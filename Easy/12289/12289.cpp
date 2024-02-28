#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int countSameChar(const string& a, const string& b)
{
    int count = 0;
    int size = min(a.size(), b.size());
    for (int i = 0; i < size; ++i)
    {
        if (a[i] == b[i])
            ++count;
    }
    return count;
}

int main()
{
    int t;
    cin >> t;
    string input;
    while (t--)
    {
        cin >> input;
        if (countSameChar("three", input) >= 4)
            cout << "3\n";
        else if (countSameChar("two", input) >= 2)
            cout << "2\n";
        else
            cout << "1\n";
    }
    return 0;
}