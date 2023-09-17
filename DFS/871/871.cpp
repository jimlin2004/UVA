#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int m, n;
int currCount;
int grid[30][30];
int direct[8][2] = {
    {0,  1}, { 1,  1}, { 1, 0}, { 1, -1},
    {0, -1}, {-1, -1}, {-1, 0}, {-1,  1}
};

bool isValid(int x, int y)
{
    return (0 <= x && x < n && 0 <= y && y < m);
}

void dfs(int x, int y)
{
    grid[y][x] = 0;
    ++currCount;
    int newX, newY;
    for (int i = 0; i < 8; ++i)
    {
        newX = x + direct[i][0];
        newY = y + direct[i][1];
        if (isValid(newX, newY))
        {
            if (grid[newY][newX] == 1)
                dfs(newX, newY);
        }
    }
}

int main()
{
    int Case;
    scanf("%d", &Case);
    getchar(); // for \n
    getchar(); // for \n
    
    bool flag = false;
    while (Case--)
    {
        int j = 0;
        char input[30];
        int size;
        while (fgets(input, 30, stdin))
        {
            size = strlen(input) - 1; // -1 for \n
            if (size == 0)
                break;
            else
                n = size;
            for (int i = 0; i < size; ++i)
                grid[j][i] = input[i] - '0';
            ++j;
        }
        m = j;
        int res = 0;
        for (int j = 0; j < m; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                if (grid[j][i] == 1)
                {
                    currCount = 0;
                    dfs(i, j);
                    res = max(currCount, res);
                }
            }
        }
        if (flag)
            printf("\n");
        else
            flag = true;
        printf("%d\n", res);
    }
    return 0;
}