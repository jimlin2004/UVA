#include <cstdio>
#include <queue>
using namespace std;

struct Task
{
    int ID, period, time;
    bool operator < (const Task& other) const
    {
        if (this->time == other.time)
            return this->ID > other.ID;
        return this->time > other.time;
    }
};

int main()
{
    char input[100];
    priority_queue<Task> pq;
    Task task;
    while (scanf("%s", input) && (input[0] != '#'))
    {
        scanf("%d %d", &task.ID, &task.period);
        task.time = task.period;
        pq.push(task);
    }

    int t;
    scanf("%d", &t);
    while (t--)
    {
        task = pq.top();
        pq.pop();
        printf("%d\n", task.ID);
        task.time += task.period;
        pq.push(task);
    }
    return 0;
}