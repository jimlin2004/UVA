#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

vector<long long> factorial = {1, 1};

/*
陷阱題
這題有特殊情況:
    F(n) = n * F(n - 1)
    n = 0 -> F(0) = n * F(-1) -> F(-1) = F(0) / 0 -> overflow
    n = -1 -> F(-1) = -1 * F(-2) -> F(-2) = -F(-1) -> underflow
    n = -2 -> F(-2) = -2 * F(-3) -> F(-3) = (F(-2) / (-2)) -> F(-3) = F(-1), 因為正無限 -> overflow
    ...以此類推
*/

int main()
{
    long long fact = 1;
    for (int i = 2;; ++i)
    {
        fact *= i;
        if (fact > 6227020800)
            break;
        factorial.emplace_back(fact);
    }
    int n;
    int limit = factorial.size();
    while (scanf("%d", &n) != EOF)
    {
        if (n >= limit)
            puts("Overflow!");
        else if (n < 0)
        {
            if (abs(n) % 2 == 0)
                puts("Underflow!");
            else
                puts("Overflow!");
        }
        else if (factorial[n] < 10000)
            puts("Underflow!");
        else
            printf("%lld\n", factorial[n]);
    }
    return 0;
}