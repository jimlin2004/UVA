#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
    這題是suffix array的題目
    此為老師的版本
    利用SA的height去找最長且重複m次以上的字串
    height -> 處理LCP (longest common prefix)

    實作看下面(慢慢咀嚼)
*/

#define maxn 40005

char str[maxn];
int Rank[maxn], tempRank[maxn];
int SA[maxn], tempSA[maxn];
int cnt[maxn]; //count sort用
int n; //輸入字串長度
int height[maxn]; //height[i] = lcp(SA[i - 1], SA[i])

//這裡不用在乎stable的問題，因為SA是所有的後綴字串，那就不可能有完全一樣的
void countingSort(int k)
{
    memset(cnt, 0, sizeof(cnt));
    //counting sort第一步
    //i + k >= n代表超出字串長度，在概念上當作字典序最小
    //至於為什麼這裡用i下面卻用SA[i]，
    //是因為其實SA[i]與i的值域都一樣，且都唯一不重複，所以用i去算就行了
    //所以也可以將for裡的i改用SA[i]
    for (int i = 0; i < n; ++i)
        ++cnt[(i + k < n) ? Rank[i + k] : 0];
    
    //counting sort第二步
    // <----老師版---->
    // int temp;
    // int prefixSum = 0; //如同counting sort要做的prefix sum，但不用陣列實作

    //這裡取300是ascii最大256，但取個整數300 or n(即str[]長度)
    //要取300是因為第一次的Rank[]時，Rank[]是由ascii產生，
    //但之後的Rank[]是算出來的Rank值，所以maxIndex改取n
    //同時若n > 300，那就都沒關係了，要防止的是第一次Rank[] based on ascii出問題
    int maxIndex = max(300, n);
    // <----老師版---->
    // for (int i = 0; i < maxIndex; ++i)
    // {
    //     temp = cnt[i];
    //     cnt[i] = prefixSum;
    //     prefixSum += temp;
    // }
    //<----我改一下的版本---->
    for (int i = 1; i < maxIndex; ++i)
    {
        cnt[i] += cnt[i - 1];
    }
    
    //counting sort第三步
    // <----老師版---->
    // for (int i = 0; i < n; ++i)
    //     tempSA[cnt[(SA[i] + k < n) ? Rank[SA[i] + k] : 0]++] = SA[i];
    for (int i = n - 1; i >= 0; --i)
        tempSA[--cnt[(SA[i] + k < n) ? Rank[SA[i] + k] : 0]] = SA[i];
    for (int i = 0; i < n; ++i)
        SA[i] = tempSA[i];
}

//每次counting sort要O(n)，倍增法要做log(n)次，所以為O(nlogn)
void buildSA()
{
    //Rank[]初始時直接用ascii排就好，因為Rank[]的功能只是可以分出字串大小關係
    for (int i = 0; i < n; ++i)
        Rank[i] = str[i] - '$'; //用$是因為'$'比所有字母的ascii小，其實沒有減不會影響答案的正確性
    //一開始SA的每一項等於後綴字串的開頭index
    for (int i = 0; i < n; ++i)
        SA[i] = i;
    
    // 倍增排序法(prefix-doubling algorithm) + counting sort
    int r;
    for (int k = 1; k < n; k <<= 1)
    {
        countingSort(k); //與radix sort同理，先做後面
        countingSort(0); //再做前面的位數
        //以下開始重新編號Rank[]
        tempRank[SA[0]] = r = 0;
        for (int i = 1; i < n; ++i)
            tempRank[SA[i]] = (Rank[SA[i]] == Rank[SA[i - 1]] && Rank[SA[i] + k] == Rank[SA[i - 1] + k]) ? r : ++r;
    
        for (int i = 0; i < n; ++i)
            Rank[i] = tempRank[i];
        // 若Rank[SA[n - 1]] == n - 1代表Rank[]已經沒有相同的值了，也就是分好了，就可以提早結束
        if (Rank[SA[n - 1]] == n - 1)
            break;
    }
}

//build height[]
//O(n)
//過程看例子.png
//有個定理: height[Rank[i]] >= height[Rank[i - 1]] - 1
void buildHA()
{
    //若SA[i] = {1, 4, 2, 3, 0} -> Rank[] = {4, 0, 2, 3, 1}
    //其實Rank[]就是SA的字典序，如字典序最小的是以1開始的後綴
    //因此SA[Rank[i]] = k -> 所有的後綴字串第i小的是以k為開頭的字串
    //可以觀察到SA[Rank[i]] = i
    for (int i = 0; i < n; ++i)
        Rank[SA[i]] = i;
    int k;
    for (int i = 0; i < n; ++i)
    {
        // Rank[i] == 0 -> 以i開始的後綴是字典序最小的，height[]一定等於0
        if (Rank[i] == 0)
        {
            height[Rank[i]] = 0;
            continue;
        }
        if (i == 0 || height[Rank[i - 1]] <= 1)
            k = 0;
        else
            k = height[Rank[i - 1]] - 1; //字典序下一個會比上一個長度小1
        // 算SA的字典序第i個與第i - 1個的lcp
        while (str[SA[Rank[i] - 1] + k] == str[SA[Rank[i]] + k])
            ++k;
        height[Rank[i]] = k;
    }
}

int main()
{
    int m;
    while (scanf("%d", &m) && m)
    {
        scanf("%s", str);
        n = (int)strlen(str);
        //此程式最後要多一個$，不然程式會錯
        str[n++] = '$';
        if (m == 1)
        {
            //如果m = 1，那最長符合題意的就是str整串本串
            printf("%d %d\n", n - 1, 0);
            continue;
        }
        buildSA();
        buildHA();
        // 二分搜答案，也就是利用長度的單調性
        int l = 1, r = n;
        int mid;
        int res = -1, resPos;
        while (l <= r)
        {
            mid = (l + r) / 2;

            //檢查答案
            //c從1開始，字串與字串本身有相同的前綴且LCP >= mid
            int c = 1, maxC = 0, maxPos = 0;
            //0 ~ n，到n的原因是避免最後一路結束卻沒有紀錄到答案，為了方便所以直接最後強制檢查答案
            //利用suffix array建出來的height[]去搜可能的字串答案
            for (int i = 0; i <= n; ++i)
            {
                if (i != n && height[i] >= mid)
                    ++c;
                else
                {
                    if (c > maxC)
                        maxC = c;
                    if (c >= m)
                    {
                        int j = i;
                        do
                        {
                            --j;
                            maxPos = max(maxPos, SA[j]);
                        } while (height[j] >= mid && j >= 0);
                    }
                    c = 1;
                }
            }

            //如果答案是可以的，那就試試看能不能更大，所以l = mid + 1
            if (maxC >= m)
            {
                l = mid + 1;
                res = mid;
                resPos = maxPos;
            }
            else
                r = mid - 1;
        }

        if (res == -1)
            puts("none");
        else
            printf("%d %d\n", res, resPos);
    }
    return 0;
}