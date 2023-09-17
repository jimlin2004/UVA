#include <iostream>
#include <cstring>
using namespace std;

char grid[105][105];
int m, n;
int direct[8][2] = {
    {1,  0}, {1, -1}, {0, -1}, {-1, -1},
    {-1, 0}, {-1, 1}, {0,  1}, {1,   1}
};

bool isValid(int x, int y)
{
    return (0 <= x && x < n && 0 <= y && y < m);
}

void dfs(int x, int y)
{
    if (grid[y][x] == '*')
        return;
    grid[y][x] = '*';
    int newX, newY;
    for (int i = 0; i < 8; ++i)
    {
        newX = x + direct[i][0];
        newY = y + direct[i][1];
        if (isValid(newX, newY))
        {
            if (grid[newY][newX] == '@')
            {
                dfs(newX, newY);
            }
        }
    }
}

int main()
{
    while ((cin >> m >> n) && (m | n))
    {
        for (int j = 0; j < m; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                cin >> grid[j][i];
            }
        }

        int res = 0;
        for (int j = 0; j < m; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                if (grid[j][i] == '@')
                {
                    ++res;
                    dfs(i, j);
                }
            }
        }
        cout << res << '\n';
    }
    return 0;
}