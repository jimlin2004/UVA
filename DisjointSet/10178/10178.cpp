#include <cstdio>
#include <cstring>
using namespace std;

//不能用歐拉公式 V - E + R = 2，因為題目不保證圖相連
//利用併查集，每有一個環就是切出一個face

int parent[128]; //A~Z、a~z，乾脆開Ascii的大小
int res;

int findRoot(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findRoot(parent[x]);
}

void Union(int x, int y)
{
    int r1 = findRoot(x);
    int r2 = findRoot(y);
    if (r1 == r2)
    {
        ++res; //有環出現
        return;
    }
    if (parent[r1] < parent[r2])
    {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }
    else
    {
        parent[r2] += parent[r1];
        parent[r1] = r2;
    }
}

int main()
{
    int n, e;
    while (scanf("%d %d", &n, &e) != EOF)
    {
        res = 1; // 最一開始即是一個face
        memset(parent, -1, sizeof(parent));
        char u, v;
        for (int i = 0; i < e; ++i)
        {
            getchar();//for \n
            scanf("%c %c", &u, &v);
            Union(u, v);
        }

        printf("%d\n", res);
    }
    return 0;
}