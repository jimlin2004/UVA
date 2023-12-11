#include <iostream>
using namespace std;

int getD(char c)
{
    switch (c)
    {
    case 'N':
        return 0;
    case 'E':
        return 1;
    case 'S':
        return 2;
    case 'W':
        return 3;
    default:
        break;
    }
    return -1;
}

char getDChar(int d)
{
    switch (d)
    {
    case 0:
        return 'N';
    case 1:
        return 'E';
    case 2:
        return 'S';
    case 3:
        return 'W';
    
    default:
        break;
    }
    return '\0';
}

bool shouldIgnore[55][55];

int main()
{
    int direct[4][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };

    int bx, by;
    cin >> bx >> by;
    int x, y;
    int d;
    char c;
    string command;
    while (cin >> x >> y >> c)
    {
        d = getD(c);
        bool falled = false;
        cin >> command;
        for (char com: command)
        {
            if (com == 'F')
            {
                x += direct[d][0];
                y += direct[d][1];
                if (0 > x || x > bx)
                {
                    x -= direct[d][0];
                    y -= direct[d][1];
                    if (!shouldIgnore[x][y])
                    {
                        falled = true;
                        shouldIgnore[x][y] = true;
                        break;
                    }
                }
                else if (0 > y || y > by)
                {
                    x -= direct[d][0];
                    y -= direct[d][1];
                    if (!shouldIgnore[x][y])
                    {
                        falled = true;
                        shouldIgnore[x][y] = true;
                        break;
                    }
                }
            }
            else if (com == 'R')
            {
                d = (d + 1) % 4;
            }
            else if (com == 'L')
            {
                --d;
                if (d == -1)
                    d = 3;
            }
        }

        cout << x << ' ' << y << ' ' << getDChar(d);
        if (falled)
            cout << " LOST";
        cout << '\n';
    }
    return 0;
}