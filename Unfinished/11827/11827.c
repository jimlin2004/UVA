#include <stdio.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

int gcd(int a, int b)
{
    return (b == 0) ? (a) : (gcd(b, a % b));
}

int main()
{
    int N;
    scanf("%d", &N);
    getchar(); //吃掉\n
    int data[100];
    int num;
    char c;
    int len;
    int max_gcd;
    for (int k = 0; k < N; k++)
    {
        len = 0;
        max_gcd = -1;
        while (scanf("%c", &c))
        {
            if (c == '\n')
            {
                if (num != 0)
                {
                    data[len] = num;
                    len++;
                }
                break;
            }
            else if (c == ' ')
            {
                if (num != 0)
                {
                    data[len] = num;
                    num = 0;
                    len++;
                }
            }
            else
            {
                num = num * 10 + (c - '0');
            }
        }
        for (int i = 0; i < len; i++)
            for (int j = i + 1; j < len; j++)
            {
                max_gcd = max(max_gcd, gcd(data[i], data[j]));
            }
        printf("%d\n", max_gcd);
    }
    return 0;
}