#include <cstdio>
using namespace std;

int main()
{
    int a, b;
    while (scanf("%d %d", &a, &b) && (a || b))
    {
        int carry = 0;
        int count  = 0;
        int digitalSum;
        while (a && b)
        {
            digitalSum = (a % 10) + (b % 10) + carry;
            carry = digitalSum / 10;
            if (digitalSum >= 10)
                ++count;
            a /= 10;
            b /= 10;
        }
        while (a)
        {
            digitalSum = (a % 10) + carry;
            carry = digitalSum / 10;
            if (digitalSum >= 10)
                ++count;
            a /= 10;
        }
        while (b)
        {
            digitalSum = (b % 10) + carry;
            carry = digitalSum / 10;
            if (digitalSum >= 10)
                ++count;
            b /= 10;
        }

        if (count == 0)
        {
            puts("No carry operation.");
        }
        else if (count == 1)
        {
            puts("1 carry operation.");
        }
        else
        {
            printf("%d carry operations.\n", count);
        }
    }
    return 0;
}