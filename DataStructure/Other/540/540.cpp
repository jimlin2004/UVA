#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int maxn = 999999 + 5;
const int maxt = 1000 + 5;

//紀錄幾號在哪個team
int teamNumber[maxn];
//紀錄team在queue的index
int teamQueueIndexMp[maxt];
vector<queue<int>> teamQueue;
//teamQueue最前面的index
int teamQueueHead;

int main()
{
    int Case = 0;

    int t;
    while (scanf("%d", &t) != EOF && t)
    {
        printf("Scenario #%d\n", ++Case);

        int n;

        memset(teamNumber, -1, sizeof(teamNumber));
        memset(teamQueueIndexMp, -1, sizeof(teamQueueIndexMp));
        teamQueue.clear();
        teamQueueHead = 0;

        int teamCount = 0;
        for (int i = 0; i < t; ++i)
        {
            scanf("%d", &n);
            int element;
            for (int j = 0; j < n; ++j)
            {
                scanf("%d", &element);
                teamNumber[element] = teamCount;
            }
            ++teamCount;
        }

        char cmd[20];
        while (scanf("%s", cmd))
        {
            if (cmd[0] == 'S')
                break;
            if (cmd[0] == 'E')
            {
                int element;
                scanf("%d", &element);
                int teamQueueIndex = teamQueueIndexMp[teamNumber[element]];
                if (teamQueueIndex == -1)
                {
                    queue<int> q;
                    q.push(element);
                    teamQueue.push_back(q);
                    teamQueueIndexMp[teamNumber[element]] = teamQueue.size() - 1;
                }
                else
                {
                    teamQueue[teamQueueIndex].push(element);
                }
            }
            else if (cmd[0] == 'D')
            {
                queue<int>& q = teamQueue[teamQueueHead];
                int headElement = q.front();
                printf("%d\n", headElement);
                q.pop();
                if (q.size() == 0)
                {
                    teamQueueIndexMp[teamNumber[headElement]] = -1;
                    ++teamQueueHead;
                }
            }
        }
        puts("");
    }
    return 0;
}