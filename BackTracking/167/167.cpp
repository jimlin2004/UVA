#include <iostream>
using namespace std;

int chessboard[9][9];
int queens[9];
int totalMax;

bool check(int c, int r)
{
    for (int i = 1; i < c; i++)
    {
        if (queens[i] == r)
            return false;
        if (abs(i - c) == abs(queens[i] - r))
            return false;
    }
    return true;
}

void backTracking(int c)
{
    if (c == 9)
    {
        int total = 0;
        for (int i = 1; i <= 8; i++)
        {
            total += chessboard[i][queens[i]];
            totalMax = max(totalMax, total);
        }
    }
    for (int i = 1; i <= 8; i++)
    {
        if (check(c, i))
        {
            queens[c] = i;
            backTracking(c + 1);
        }
    }
}

int main()
{
    int k;
    scanf("%d", &k);
    while (k--)
    {
        totalMax = 0;
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
                scanf("%d", &chessboard[i][j]);
        backTracking(1);
        printf("%5d\n", totalMax);
    }
    return 0;
}