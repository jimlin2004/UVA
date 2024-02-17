#include <cstdio>
#include <cstring>
#include <cstdlib>

char num[1005];

int main()
{
    while (scanf("%s", &num))
    {
        int len = strlen(num);
        if (num[0] == '0' && len == 1)
            break;
        int oddSum = 0;
        int evenSum = 0;
        for (int i = 0; i < len; ++i)
        {
            if (i % 2 == 0)
                evenSum += num[i] - '0';
            else
                oddSum += num[i] - '0';
        }
        //oddSum與evenSum相減 = 0 或 11的倍數
        if (abs(oddSum - evenSum) % 11 == 0)
            printf("%s is a multiple of 11.\n", num);
        else
            printf("%s is not a multiple of 11.\n", num);
    }
    return 0;
}