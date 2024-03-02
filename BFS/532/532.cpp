#include <iostream>
#include <queue>
using namespace std;

//基礎BFS走迷宮3D version

struct Point
{
    int x, y, z;
};

int L, R, C;
char maze[35][35][35];

int direct[6][3] = {
    {1, 0, 0}, {0, 1, 0}, {-1, 0, 0},
    {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
};

inline bool valid(int x, int y, int z)
{
    return (1 <= x && x <= C) && (1 <= y && y <= R) && (1 <= z && z <= L);
}

void bfs(const Point& start)
{
    queue<pair<Point, int>> q;
    q.push({start, 0});
    while (!q.empty())
    {
        Point point = q.front().first;
        int d = q.front().second;
        q.pop();

        if (maze[point.y][point.x][point.z] == '#')
            continue;
        if (maze[point.y][point.x][point.z] == 'E')
        {
            printf("Escaped in %d minute(s).\n", d);
            return;
        }
        maze[point.y][point.x][point.z] = '#';
        int newX, newY, newZ;
        for (int dir = 0; dir < 6; ++dir)
        {
            newX = point.x + direct[dir][0];
            newY = point.y + direct[dir][1];
            newZ = point.z + direct[dir][2];
            if (valid(newX, newY, newZ))
            {
                if (maze[newY][newX][newZ] != '#')
                {
                    q.push({{newX, newY, newZ}, d + 1});
                }
            }
        }
    }
    puts("Trapped!");
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while ((cin >> L >> R >> C) && (L && R && C))
    {
        Point start;
        for (int k = 1; k <= L; ++k)
        {
            for (int i = 1; i <= R; ++i)
            {
                for (int j = 1; j <= C; ++j)
                {
                    cin >> maze[i][j][k];
                    if (maze[i][j][k] == 'S')
                    {
                        start = {j, i, k};
                    }
                }
            }
        }

        bfs(start);
    }
    return 0;
}