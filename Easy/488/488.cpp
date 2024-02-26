#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    bool first = true;
    while (t--)
    {
        int h, num;
        cin >> h >> num;

        if (first)
            first = false;
        else
            cout << '\n';

        for (int n = 0; n < num; ++n)
        {
            if (n != 0)
                cout << '\n';
            for (int i = 1; i <= h; ++i)
            {
                for (int j = 1; j <= i; ++j)
                {
                    cout << i;
                }
                cout << '\n';
            }
            for (int i = h - 1; i >= 1; --i)
            {
                for (int j = 1; j <= i; ++j)
                {
                    cout << i;
                }
                cout << '\n';
            }
        }
        
    }
    return 0;
}