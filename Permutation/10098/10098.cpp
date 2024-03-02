#include <iostream>
#include <algorithm>
using namespace std;

//next_permutation練習

int main()
{
    int t;
    cin >> t;
    string input;
    while (t--)
    {
        cin >> input;
        sort(input.begin(), input.end());

        cout << input << '\n';
        while (next_permutation(input.begin(), input.end()))
        {
            cout << input << '\n';
        }

        cout << '\n';
    }
    return 0;
}