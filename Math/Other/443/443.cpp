#include <cstdio>
#include <algorithm>
using namespace std;

/*
概念:
    第n個數一定是前n - 1個數 x2 or x3 or x5 or x7得來，
    也就是前n - 1個數x2 or x3 or x5 or x7中找出大於nums[n - 1]的最小值

    但不用全部n - 1數重找一遍，
    ex: 12由6 * 2得來，在找12以後的數字時，只需要從6之後的數開始x2試試看
        ，因為6以前的數不可能大於12，如此x2 or x3 or x5 or x7都是一樣的
        道理，用p2, p3, p5, p7去紀錄最後的位置
*/

#define maxn 5850

int main()
{
    unsigned long long nums[maxn];
    nums[0] = 0;
    nums[1] = 1;
    int p2 = 1, p3 = 1, p5 = 1, p7 = 1;
    for (int i = 2; i < maxn; ++i)
    {
        while (nums[p2] * 2 <= nums[i - 1]) ++p2;
        while (nums[p3] * 3 <= nums[i - 1]) ++p3;
        while (nums[p5] * 5 <= nums[i - 1]) ++p5;
        while (nums[p7] * 7 <= nums[i - 1]) ++p7;
        nums[i] = min({nums[p2] * 2, nums[p3] * 3, nums[p5] * 5, nums[p7] * 7});
    }

    int n;
    while (scanf("%d", &n) && n)
    {
        printf("The %d", n);
        if( n % 10 == 1 && n % 100 != 11 )
        {
            printf("st");
        }
        else if( n % 10 == 2 && n % 100 != 12 )
        {
            printf("nd");
        }
        else if( n % 10 == 3 && n % 100 != 13 )
        {
            printf("rd");
        }
        else 
        {
            printf("th");
        }
        printf(" humble number is %d.\n", nums[n]);
    }
    return 0;
}