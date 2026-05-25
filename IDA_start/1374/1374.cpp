#include <bits/stdc++.h>
using namespace std;

/*
    題意是指要算出x^n，可以用最少多少次乘法與除法算出來?
    所以每次乘的時候使用算過的，除的時候也是

    解法:
    這題沒有很好的辦法greedy或dp算出最優次數
    所以改用dfs的方式暴力搜尋
    但dfs無法保證最優解，也需要剪枝加速
    所以正確做法是使用IDA*
    每一次增加一點深度直到搜到第一個解，那個解一定是最少步數的(跟bfs同理)

    詳細見程式
*/

int maxd; // 目前搜尋的最深深度限制
int n; // 題目的x^n

// dfs路徑上每個node算到多少x^p
// 如pathNodes[0] -> 深度為0的那個路徑node算到多少x^p，pathNodes[1] -> 深度為1的那個路徑node算到多少x^p
int pathNodes[30]; 

bool dfs(int depth)
{
    // 如果到了深度限制，檢查是不是算出x^n了
    if (depth == maxd)
    {
        return pathNodes[depth] == n;
    }

    // 剪枝技巧:
    // 在嘗試dfs搜尋的時候，如果目前這個點答案(x^p)用最快增加冪次的方式(不斷平方操作)
    // 仍然 x^p < x^n，那這個點就永遠不可能算出答案
    if ((pathNodes[depth] << (maxd - depth)) < n)
    {
        return false;
    }

    // 往回看之前dfs路徑上曾經算過哪些冪次
    for (int i = depth; i >= 0; --i)
    {
        // 下一層試試看用 x^(pathNodes[depth] + pathNodes[i])的
        pathNodes[depth + 1] = pathNodes[depth] + pathNodes[i];
        // 限制在1000是題目資料範圍，也算是剪枝
        if (pathNodes[depth + 1] <= 1000 && dfs(depth + 1))
            return true;
        
        // 下一層試試看用 x^(pathNodes[depth] - pathNodes[i])的
        pathNodes[depth + 1] = pathNodes[depth] - pathNodes[i];
        // 題目說過程中不能有負的冪次，也算是剪枝
        if (pathNodes[depth + 1] >= 0 && dfs(depth + 1))
            return true;
    }

    return false;
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        if (n == 1)
        {
            printf("0\n");
            continue;
        }

        // 第一層一定是x^1的
        pathNodes[0] = 1;
        maxd = 1;

        // 開始IDA*暴力搜尋
        while (true)
        {
            if (dfs(0))
            {
                printf("%d\n", maxd);
                break;
            }

            ++maxd;
        }
    }
    return 0;
}

