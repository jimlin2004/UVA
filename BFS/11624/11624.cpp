#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool visited[1001][1001];
char grid[1001][1001];

int direction[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

int r, c;
int jx, jy; // Joe的
int t[1001][1001];

struct Cell
{
    int x, y, time;
};

bool check(int x, int y)
{
    return (x >= 0 && x < c) && (y >= 0 && y < r);
}

void solve(queue<Cell>& q)
{
    // 做兩次bfs，計算火的bfs與Joe的bfs，紀錄個別的時間，
    // 若火的time > Joe's time，則Joe被火燒
    // 反之Joe逃生
    // 注意，火不只有一個
    
    // 火
    while (!q.empty())
    {
        Cell cell = q.front();
        q.pop();

        if (visited[cell.y][cell.x])
            continue;
        visited[cell.y][cell.x] = true;
        // t[cell.y][cell.x] = min(cell.time, t[cell.y][cell.x]); //不需要(因為會最近的先到)
        t[cell.y][cell.x] = cell.time;
        for (int i = 0; i < 4; ++i)
        {
            int nextX = cell.x + direction[i][0];
            int nextY = cell.y + direction[i][1];
            if (grid[nextY][nextX] == '#')
                continue;
            if (check(nextX, nextY))
            {
                q.push({nextX, nextY, cell.time + 1});
            }
        }
    }

    // Joe
    memset(visited, false, sizeof(visited));

    q.push({jx, jy, 0});

    while (!q.empty())
    {
        Cell cell = q.front();
        q.pop();

        if (visited[cell.y][cell.x])
            continue;
        visited[cell.y][cell.x] = true;
        if (t[cell.y][cell.x] <= cell.time)
            continue;
        for (int i = 0; i < 4; ++i)
        {
            int nextX = cell.x + direction[i][0];
            int nextY = cell.y + direction[i][1];
            if (grid[nextY][nextX] == '#')
                continue;
            if (!check(nextX, nextY))
            {
                if (t[cell.y][cell.x] > cell.time)
                    printf("%d\n", cell.time + 1);
                else
                    printf("IMPOSSIBLE\n");
                return;
            }
            
            else
            {
                q.push({nextX, nextY, cell.time + 1});
            }
        }
    }
    printf("IMPOSSIBLE\n");
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &r, &c);
        memset(visited, false, sizeof(visited));
        memset(t, 0x3f, sizeof(t));
        memset(grid, 0, sizeof(grid));
        getchar(); // for \n
        queue<Cell> q;
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                grid[i][j] = getchar();
                if (grid[i][j] == 'J')
                {
                    jx = j;
                    jy = i;
                }
                if (grid[i][j] == 'F')
                {
                    q.push({j, i, 0});
                }
            }
            getchar();// for \n
        }
        solve(q);
        while(!q.empty())
            q.pop();
    }
    return 0;
}