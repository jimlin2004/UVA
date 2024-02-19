#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//大數相加

char num1[205];
char num2[205];

char sum[205];

void add(char src1[], char src2[], char dst[])
{
    int index = 0;
    int src1Size = strlen(src1);
    int src2Size = strlen(src2);
    int carry = 0;
    int res = 0;
    while (index < src1Size && index < src2Size)
    {
        res = num1[index] - '0' + num2[index] - '0' + carry;
        carry = res / 10;
        dst[index] = (res % 10) + '0';
        ++index;
    }
    while (index < src1Size)
    {
        res = num1[index] - '0' + carry;
        carry = res / 10;
        dst[index] = (res % 10) + '0';
        ++index;
    }
    while (index < src2Size)
    {
        res = num2[index] - '0' + carry;
        carry = res / 10;
        dst[index] = (res % 10) + '0';
        ++index;
    }
    if (carry != 0)
        dst[index] = carry + '0';
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", &num1);
        scanf("%s", &num2);
        memset(sum, 0, sizeof(sum));
        add(num1, num2, sum);
        int len = strlen(sum);
        int index = 0;
        while (sum[index] == '0')
            ++index;
        printf("%s\n", sum + index);
    }
    return 0;
}