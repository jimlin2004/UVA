#include <cstdio>
#include <cstring>
using namespace std;

#define maxn 100005

/*
核心概念:
    s是循環程度，n是history長度
    history有3個部分，分別是前面不完整、中間完整、後面不完整
    只有前面不完整的部分是我們要考慮的部分，
    因為中間完整的部分包含一組或多組循環(不是每個測資都有中間部分)
    我們在前面不完整的部分找可以作為循環的開頭(假設index為start)
    則start, start + s, start + 2s...直到index <= n皆應是循環的開頭
    最後到了start + a * s > n的index: (start + a * s)(a是正整數)就是未來可能Reshuffle的位置
    那麼res++
    同時這個方法不會重複計算到相同的未來Reshuffle位置
    因為我們只從前面不完整的部分去找到可以是循環開頭的去位移(每次+s直到index > n)找到新的未來可能Reshuffle的位置
    可以是循環開頭的位置(設為start)滿足
        1. start以前(不包含)有s個不同的數字
        2. start以後(包含)  有s個不同的數字
    在前面不完整的部分中在histroy以前的數字可以假設為任何數字
    及後面不完整的部分中在histroy後面的數字可以假設為任何數字
    因此有了以下的算法:
        vaildForward[i]  代表i以前(包含)有沒有s個不同數字(true / false)
        vaildBackward[i] 代表i以後(包含)有沒有s個不同數字(true / false)
        vaildForward、vaildBackward的求法應用滑動窗戶
        最後再scan一遍找出所有循環開頭即可
    <注1>
        能直接(i > n) -> diffNum++的原因是:
        1. 假如s = 4，窗戶: 1123，此時diffNum = 3，窗戶移動後變123X，diffNum = 4 -> 找到一組
        2. 窗戶: 2113，此時diffNum = 3，窗戶移動後變113X，但diffNum還是 = 3，不會影響答案，變成1的case討論
        3. 窗戶: 1234，此時diffNum = 4，窗戶移動後變234X，diffNum = 4 -> 找到一組
        4. 窗戶: 1112，此時diffNum = 2，窗戶移動後變112X，diffNum = 3 -> 變成1的case討論
        其餘狀況可以類推，可以發現(i > n) diffNum直接 + 1都是合理操作
*/

//向前有沒有s個不同的數
bool vaildForward[maxn * 2];
//向後有沒有s個不同的數
bool vaildBackward[maxn * 2];
int count[maxn];
int history[maxn];

int solve(int s, int n)
{
    memset(count, 0, sizeof(count));
    memset(vaildForward, false, sizeof(vaildForward));
    memset(vaildBackward, false, sizeof(vaildBackward));

    //不一樣的數字個數
    int diffNum = 0;

    for (int i = 1; i <= s + n; ++i)
    {
        //找到後面一組有s個不同數字的pair
        if (i > s && diffNum == s)
            vaildBackward[i - s] = true;
        //滑動窗戶
        if (i > s)
        {
            --count[history[i - s]];
            if (count[history[i - s]] == 0)
                --diffNum;
        }
        //<注1>
        if (i > n)
            ++diffNum;
        else
        {
            if (count[history[i]] == 0)
                ++diffNum;
            ++count[history[i]];
        }

        //紀錄vaildForward
        if (i <= s && diffNum == i)
            vaildForward[i] = true;
    }
    
    int res = 0;
    bool ok;
    for (int i = 1; i <= s; ++i)
    {
        if (i != 1 && !vaildForward[i - 1])
            continue;
        ok = true;
        for (int j = i; j <= n && ok; j += s)
            if (!vaildBackward[j])
                ok = false;
        if (ok)
            ++res;
    }
    return res;
}

int main()
{
    int t;
    int s, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &s, &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &history[i]);
        }

        printf("%d\n", solve(s, n)); 
    }
    return 0;
}