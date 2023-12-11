#include <cstdio>
#include <vector>
using namespace std;

int main()
{
    //觀察題
    //算到每個斜邊有的數量
    vector<int> edges;
    edges.emplace_back(0);
    int count = 1;
    while (edges.back() <= 10000000)
    {
        edges.emplace_back(edges.back() + count);
        ++count;
    }

    int n;
    while (scanf("%d", &n) != EOF)
    {
        //找出在哪個斜邊
        int i;
        for (i = 1; n > edges[i]; ++i);
        printf("TERM %d IS ", n);
        //奇數排由上往下
        if (i & 1)
        {
            printf("%d/%d\n", edges[i] - n + 1, n - edges[i - 1]);
        }
        //偶數排由下往上
        else
        {
            printf("%d/%d\n", n - edges[i - 1], edges[i] - n + 1);
        }
    }
    return 0;
}