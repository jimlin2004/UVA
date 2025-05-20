#include <bits/stdc++.h>
using namespace std;


int A[10];
bool res;

bool dfs(int i, int ans)
{
    if (i == 5)
    {
        if (ans == 23)
            res = true;
        return res;
    }

    if (dfs(i + 1, ans + A[i]))
        return true;
    if (dfs(i + 1, ans - A[i]))
        return true;
    if (dfs(i + 1, ans * A[i]))
        return true;

    return false;
}

int main()
{
    while (1)
    {
        for (int i = 0; i < 5; ++i)
            scanf("%d", &A[i]);
        
        bool done = true;
        for (int i = 0; i < 5; ++i)
        {
            if (A[i] != 0)
                done = false;
        }
        if (done)
            break;
        
        res = false;

        // 所有排列組合都要試
        sort(A, A + 5);
        do
        {
            dfs(1, A[0]);
            if (res)
                break;
        } while (next_permutation(A, A + 5));
        

        puts((res) ? "Possible" : "Impossible");
    }

    return 0;
}