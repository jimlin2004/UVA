#include <cstdio>

int squares[1005];

int findLess(int n)
{
    int l = 0, r = 1004;
    int mid;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (squares[mid] < n)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return r;
}

int findGreater(int n)
{
    int l = 0, r = 1004;
    int mid;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (squares[mid] > n)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

int main()
{
    for (int i = 0; i < 1005; ++i)
    {
        squares[i] = i * i;
    }

    int a, b;
    int lessIndex, greaterIndex;
    while (scanf("%d %d", &a, &b) && a && b)
    {
        lessIndex = findLess(a);
        greaterIndex = findGreater(b);
        printf("%d\n", greaterIndex - lessIndex - 1);
    }
    return 0;
}