#include <string>
#include <iostream>
using namespace std;

int actions[105];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int q;
        cin >> q;
        int curr = 0;
        int actionIndex = 1;
        string cmd;
        while (q--)
        {
            cin >> cmd;
            if (cmd == "LEFT")
            {
                actions[actionIndex] = -1;
                ++actionIndex;
                --curr;
            }
            else if (cmd == "RIGHT")
            {
                actions[actionIndex] = 1;
                ++actionIndex;
                ++curr;
            }
            else if (cmd == "SAME")
            {
                cin >> cmd;
                int history;
                cin >> history;
                actions[actionIndex] = actions[history];
                curr += actions[actionIndex];
                ++actionIndex;
            }
        }
        cout << curr << '\n';
    }
    return 0;
}