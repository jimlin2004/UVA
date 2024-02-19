#include <cstdio>

//100是猜測的值，題目沒有講明確範圍
//注: 經過debug確認，40幾就溢位了(> 2^32)
unsigned int f[100] = {1}, m[100] = {0};

int main()
{
    for (int i = 1; i < 100; ++i)
    {
        f[i] = m[i - 1] + 1;// +1 for 不死的那隻
        m[i] = f[i - 1] + m[i - 1];
    }
    int n;
    while (scanf("%d", &n) && (n != -1))
    {
        printf("%u %u\n", m[n], f[n] + m[n]);
    }
    return 0;
}