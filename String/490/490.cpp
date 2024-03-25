#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
由左到右由上至下
改
由下至上，由右至左
*/

#define maxn 105

string inputs[maxn];

int main()
{
    int inputCount = 0;
    int maxInputLen = 0;
    while (getline(cin, inputs[inputCount]))
    {
        maxInputLen = max(maxInputLen, (int)inputs[inputCount].size());
        ++inputCount;
    }

    for (int i = 0; i < maxInputLen; ++i)
    {
        for (int j = inputCount - 1; j >= 0; --j)
        {
            if (inputs[j].size() > i)
                cout << inputs[j][i];
            else
                cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}