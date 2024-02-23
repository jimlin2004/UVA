#include <cstdio>

//直接模擬

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        int res = 0;
        if (n == 2)
        {
            ++res;
            n = 0;
        }
        int returnCola;
        while (n > 2)
        {
            res += (n / 3);
            //換回來的
            returnCola = (n % 3);
            n /= 3;
            n += returnCola;
        }
        //最後的2罐借一罐
        if (n == 2)
            ++res;
        printf("%d\n", res);
    }
    return 0;
}