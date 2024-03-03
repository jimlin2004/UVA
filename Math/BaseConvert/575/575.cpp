#include <cstdio>
#include <cstring>

char input[60];

//照著題意

int main()
{
    while (scanf("%s", input) != EOF && input[0] != '0')
    {
        long long n = 0;
        long long base2 = 2;
        int len = strlen(input);
        for (int i = len - 1; i >= 0; --i)
        {
            n += (input[i] - '0') * (base2 - 1);
            base2 <<= 1;
        }
        printf("%lld\n", n);
    }
    return 0;
}