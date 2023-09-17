#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int n;
    int move_n;
    while (scanf("%d", &n) != EOF)
    {
        if (n == 0) break;
        queue<int> q;
        for (int i = 1; i <= n; ++i)
        {
            q.push(i);
        }
        printf("Discarded cards:");
        bool flag = false;
        while (q.size() != 1)
        {
            if (flag)
                printf(", ");
            else
                printf(" ");
            flag = true;
            printf("%d", q.front());
            q.pop();
            move_n = q.front();
            q.pop();
            q.push(move_n);
        }
        printf("\nRemaining card: %d\n", q.front());
    }
    return 0;
}