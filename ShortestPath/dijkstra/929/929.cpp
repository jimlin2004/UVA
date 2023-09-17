#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int row, col;
int maze[1000][1000];
int direction[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};
bool visited[1000][1000];
int dis[1000][1000];

struct Item
{
    int x, y;
    int w;

    bool operator<(const Item& other) const
    {
        return this->w > other.w;
    }
};

inline bool isValid(int x, int y)
{
    return (x >= 0) && (x < col) && (y >= 0) && (y < row);
}

int dijkstar()
{
    priority_queue<Item> pq;
    dis[0][0] = maze[0][0];
    pq.push({0, 0, dis[0][0]});

    while (!pq.empty())
    {
        Item item = pq.top();
        pq.pop();

        if (visited[item.y][item.x])
            continue;
        visited[item.y][item.x] = true;

        for (int i = 0; i < 4; ++i)
        {
            int nx = item.x + direction[i][0];
            int ny = item.y + direction[i][1];

            if (isValid(nx, ny))
            {
                if (!visited[ny][nx])
                {
                    if (dis[ny][nx] > dis[item.y][item.x] + maze[ny][nx])
                    {
                        dis[ny][nx] = dis[item.y][item.x] + maze[ny][nx];
                        pq.push({nx, ny, dis[ny][nx]});
                    }
                }
            }
        }
    }

    return dis[row - 1][col - 1];
}

int main()
{
    int Case;
    scanf("%d", &Case);
    int test = 2;
    while (Case--)
    {
        memset(visited, false, sizeof(visited));
        memset(dis, 0x3f, sizeof(dis));

        scanf("%d", &row);
        scanf("%d", &col);
        for (int j = 0; j < row; ++j)
        {
            for (int i = 0; i < col; ++i)
            {
                scanf("%d", &maze[j][i]);
            }
        }
        
        printf("%d\n", dijkstar());
    }


    return 0;
}