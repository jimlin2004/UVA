#include <cstdio>
#include <cstring>
using namespace std;

//k很小，直接模擬

bool judge(int k, int m)
{
    int curr = 0;
    for (int i = k * 2; i > k; --i)
    {
        //每次處決一人，所以i逐漸減少
        curr = (curr - 1 + m) % i;
        //好人先死了
        if (curr < k)
            return false;
    }
    return true;
}

int solve(int k)
{
    //一定大於k，否則好人會先死
    for (int m = k + 1;; ++m)
    {
        if (judge(k, m))
            return m;
    }
    return -1;
}

int main()
{
    int ans[15];
    for (int i = 1; i < 14; ++i)
        ans[i] = solve(i);
    int k;
    while (scanf("%d", &k) && k)
    {
        printf("%d\n", ans[k]);
    }
    return 0;
}