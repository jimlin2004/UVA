#include <cstdio>
using namespace std;

#define maxn 100005

//直接建表
int table[maxn];

void buildTable()
{
    for (int i = 1; i < maxn; ++i)
    {
        int sum = i;
        int remain = i;
        while (remain > 0)
        {
            sum += remain % 10;
            remain /= 10;
        }
        if (table[sum] == 0)
            table[sum] = i;
    }
}

int main()
{
    buildTable();

    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", table[n]);
    }
    return 0;
}