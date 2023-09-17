#include <iostream>
#include <queue>
using namespace std;

bool check(const pair<int, int>& p)
{
    if (p.first > ('h' - 'a') || p.first < 0 || p.second < 1 || p.second > 8)
        return false;
    return true;
}

int main()
{
    pair<int, int> from, to;
    int n;
    pair<int, int> current;
    while (scanf("%c%d %c%d", &from.first, &from.second, &to.first, &to.second) != EOF)
    {
        bool visited[9][9] = {false};
        queue<pair<char, int>> q;
        n = 0;
        from.first -= 'a';
        to.first -= 'a';
        q.push(from);
        int size = q.size();
        
        while (!q.empty())
        {
            if (size == 0)
            {
                n++;
                size = q.size();
            }
            current = q.front();
            q.pop();
            size--;
            if (current.first == to.first && current.second == to.second)
                break;
            if (visited[current.first][current.second])
                continue;
            visited[current.first][current.second] = true;

            if (check({current.first + 1, current.second + 2}))
                q.push({current.first + 1, current.second + 2});
            if (check({current.first + 2, current.second + 1}))
                q.push({current.first + 2, current.second + 1});
            if (check({current.first + 2, current.second - 1}))
                q.push({current.first + 2, current.second - 1});
            if (check({current.first + 1, current.second - 2}))
                q.push({current.first + 1, current.second - 2});
            if (check({current.first - 1, current.second - 2}))
                q.push({current.first - 1, current.second - 2});
            if (check({current.first - 2, current.second - 1}))
                q.push({current.first - 2, current.second - 1});
            if (check({current.first - 2, current.second + 1}))
                q.push({current.first - 2, current.second + 1});
            if (check({current.first - 1, current.second + 2}))
                q.push({current.first - 1, current.second + 2});
        }
        printf("To get from %c%d to %c%d takes %d knight moves.\n", (char)(from.first + 'a'), from.second, (char)(to.first + 'a'), to.second, n);
        getchar();
    }
    return 0;
}