#include <stdio.h>
#include <math.h>
#include <map>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1) return false;
    for (int i = 2; i < n - 1; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    map<char, int> table;
    int T;
    char ch;
    bool flag;
    scanf("%d", &T);
    getchar();
    for (int k = 1; k <= T; k++)
    {
        table.clear();
        while (scanf("%c", &ch) != EOF)
        {
            if (ch == '\n')
                break;
            if (table.find(ch) != table.end())
                table[ch]++;
            else
                table[ch] = 1;
        }
        printf("Case %d: ", k);
        flag = false;
        for (std::map<char, int>::iterator it = table.begin(); it != table.end(); ++it)
        {
            if (isPrime(it->second))
            {
                printf("%c", it->first);
                flag = true;
            }
        }
        if (!flag)
            printf("empty");
        printf("\n");
    }
    return 0;
}