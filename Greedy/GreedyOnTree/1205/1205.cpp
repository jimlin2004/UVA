#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

/*
    基本上是greedy + 縮點的題目
    
    觀察到node.c最大的我們應該越早做完越好
    但是做到該node前要先走完node的所有祖先，
    因此greedy時不能只取決於node.c
    還要考慮祖先的組合

    利用縮點的概念，
    先將node新增一個 attribute w 代表node的weight(一開始都等於node.c)
    新增一個 attribute t 代表做完該縮點後的一點總共要的time
    greedy比較時利用node.w / node.t選最大代表應優先被做完的去縮點(點集合)
    node.w / node.t即代表每單位時間在那些點上的單位weight
    不斷做下去最後縮點到剩下root，root.c即是答案
    
    縮點其實就是將node與parent集合成一個點，
    node.c代表原本做完那些點的總cost，
    node.t代表原本做元那些點的總time，
    node.w代表縮完點後該縮點的weight，
    因此對於縮點時的維護為(node u 與 parent p 縮點成p):
    p.w += u.w; //u的weight被p合併
    //有待討論(1)
    p.c += p.t * u.w + u.c; //將u塗完色，併入到p的cost
    p.t += u.t; //u的時間與p合併

    //試著推出討論(1) <- 還沒推出來
    假設一開始要做p時的timer = T
    所以做完p的totalCost += T * p.c
    接著做u，此時timer = T + 1
    所以做完u的totalCost += (T + 1) * u.c
    =>  意義等同於totalCost += T * p.c + (T + 1) * u.c
    =>  把u、p看作同一個點p -> T * p.c' = T * p.c + (T + 1) * u.c
    =>  p.c' = p.c + u.c + (u.c) / T
*/

#define maxn 1005

int parent[maxn];
int t[maxn], c[maxn], w[maxn];
bool existed[maxn];

int main()
{
    int n;
    int root;

    while (scanf("%d %d", &n, &root) && (n && root))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &c[i]);

            t[i] = 1;
            existed[i] = true;
            w[i] = c[i];
        }

        int u, v;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d %d", &u, &v);
            parent[v] = u;
        }

        //O(n)找node.w / node.t最大的點
        for (int i = 1; i < n; ++i)
        {
            int k = -1;
            double maxW = -1;
            for (int j = 1; j <= n; ++j)
            {
                if (j != root && existed[j])
                {
                    if (maxW < ((double)w[j] / t[j]))
                    {
                        maxW = ((double)w[j] / t[j]);
                        k = j;
                    }
                }
            }

            for (int j = 1; j <= n; ++j)
            {
                if (parent[j] == k)
                {
                    parent[j] = parent[k];
                }
            }

            w[parent[k]] += w[k];
            c[parent[k]] += t[parent[k]] * w[k] + c[k];
            t[parent[k]] += t[k];
            existed[k] = false;
        }

        printf("%d\n", c[root]);
    }
    return 0;
}
