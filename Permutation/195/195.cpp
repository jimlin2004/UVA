#include <iostream>
#include <algorithm>
using namespace std;

//當作複習next_permutation

//字母序 -> AaBb...，不是ascii
bool cmp(char a, char b)
{
    char upperA = toupper(a);
    char upperB = toupper(b);
    if (upperA == upperB)
        return a < b;
    return upperA < upperB;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        string input;
        cin >> input;
        sort(input.begin(), input.end(), cmp);
        cout << input << '\n';
        while (next_permutation(input.begin(), input.end(), cmp))
            cout << input << '\n';
    }
    return 0;
}