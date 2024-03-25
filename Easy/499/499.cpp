#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

#define max(a, b) (a < b) ? b : a

//就統計字母數

int table[130];

int main()
{
    string line;
    while (getline(cin, line))
    {
        int maxF = 0;
        memset(table, 0, sizeof(table));
        for (char c: line)
        {
            if (!isalpha(c))
                continue;
            ++table[c];
            maxF = max(maxF, table[c]);
        }

        for (int i = 0; i < 130; ++i)
        {
            if (table[i] == maxF)
            {
                cout << (char)(i);
            }
        }
        cout << ' ' << maxF << '\n';
    }
    return 0;
}