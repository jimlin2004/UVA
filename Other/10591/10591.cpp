#include <cstdio>
#include <unordered_map>
using namespace std;

int square[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
unordered_map<int, bool> mp;

bool solve(int n)
{
    while (n != 1)
    {
        int temp = 0;
        while (n)
        {
            temp += (square[n % 10]);
            n /= 10;
        }
        n = temp;
        if (n == 1)
            return true;
        if (mp.find(n) != mp.end())
            return false;
        mp[n] = true;
    }
    return true;
}

int main()
{
    int t;
    scanf("%d", &t);
    int n;
    for (int Case = 1; Case <= t; ++Case)
    {
        mp.clear();
        scanf("%d", &n);
        printf("Case #%d: %d", Case, n);
        if (solve(n))
            puts(" is a Happy number.");
        else
            puts(" is an Unhappy number.");
    }
    return 0;
}