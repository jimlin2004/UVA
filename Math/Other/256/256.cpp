#include <cstdio>
#include <vector>
using namespace std;

vector<int> table[4];

void getTable()
{
    int divisor[4] = {10, 100, 1000, 10000};
    for (int i = 0; i < 10000; ++i)
    {
        //對每個完全平方數試試看
        int square = i * i;
        for (int j = 0; j < 4; ++j)
        {
            //如找4位數是不是quirksome number(k^2)
            //則我們只要找k -> 2位數即可
            //所以只要 < divisor的才有可能
            if (i < divisor[j])
            {
                int l = square / divisor[j];
                int r = square % divisor[j];
                if (i == l + r)
                    table[j].emplace_back(square);
            }
        }
    }
}

int main()
{
    getTable();
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int s: table[n / 2 - 1])
        {
            printf("%0*d\n", n, s);
        }
    }
    return 0;
}