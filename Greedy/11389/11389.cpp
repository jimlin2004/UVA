#include <bits/stdc++.h>
using namespace std;

/*
    白邊最長配晚上最短
    greedy
*/

#define maxn 105

int A[maxn];
int B[maxn];

int main()
{
    int n, d, r;
    while (scanf("%d %d %d", &n, &d, &r) && n && d && r)
    {
        for (int i = 0; i < n; ++i)
            scanf("%d", &A[i]);
        for (int i = 0; i < n; ++i)
            scanf("%d", &B[i]);
        
        sort(A, A + n);
        sort(B, B + n, greater<int>());

        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (A[i] + B[i] > d)
            {
                res += (A[i] + B[i] - d) * r;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}