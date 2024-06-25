#include <iostream>
using namespace std;

/*
    單純遞迴
*/

int arr[20];

void solve(int n, int h, int index)
{
    if (index == n)
    {
        if (h == 0)
        {
            for (int i = 0; i < n; ++i)
            {
                cout << arr[i];
            }
            cout << '\n';
        }
        return;
    }

    arr[index] = 0;
    solve(n, h, index + 1);
    arr[index] = 1;
    solve(n, h - 1, index + 1);
    arr[index] = 0;
}

int main()
{
    int t;
    cin >> t;

    bool first = true;
    while (t--)
    {
        int n, h;
        cin >> n >> h;

        if (first)
            first = false;
        else
            cout << '\n';
        solve(n, h, 0);
    }
    return 0;
}