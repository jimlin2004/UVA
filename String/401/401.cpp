#include <iostream>
using namespace std;

char reverseMp[255] = {};

bool isPalindrome(const string& s)
{
    if (s.empty())
        return true;
    if (s.size() == 1)
        return true;
    int l = 0, r = s.size() - 1;
    while (l <= r)
    {
        if (s[l] != s[r])
            return false;
        ++l, --r;
    }
    return true;
}

bool isMirrored(const string& s)
{
    if (s.empty())
        return true;
    if (s.size() == 1)
        return (reverseMp[s[0]] == s[0]);
    int l = 0, r = s.size() - 1;
    while (l <= r)
    {
        if (reverseMp[s[l]] == 0 || reverseMp[s[r]] == 0)
        {
            return false;
        }
        if ((s[l] != reverseMp[s[r]]) || (reverseMp[s[l]] != s[r]))
            return false;
        ++l, --r;
    }
    return true;
}

int main()
{
    reverseMp['A'] = 'A';
    reverseMp['E'] = '3';
    reverseMp['H'] = 'H';
    reverseMp['I'] = 'I';
    reverseMp['J'] = 'L';
    reverseMp['L'] = 'J';
    reverseMp['M'] = 'M';
    reverseMp['O'] = 'O';
    reverseMp['S'] = '2';
    reverseMp['T'] = 'T';
    reverseMp['U'] = 'U';
    reverseMp['V'] = 'V';
    reverseMp['W'] = 'W';
    reverseMp['X'] = 'X';
    reverseMp['Y'] = 'Y';
    reverseMp['Z'] = '5';
    reverseMp['1'] = '1';
    reverseMp['2'] = 'S';
    reverseMp['3'] = 'E';
    reverseMp['5'] = 'Z';
    reverseMp['8'] = '8';
    string s;

    while (cin >> s)
    {
        bool isPalindromeStr = isPalindrome(s);
        bool isMirroredStr = isMirrored(s);
        cout << s;
        if (!isPalindromeStr && !isMirroredStr)
            cout << " -- is not a palindrome.\n\n";
        else if (isPalindromeStr && !isMirroredStr)
            cout << " -- is a regular palindrome.\n\n";
        else if (!isPalindromeStr && isMirroredStr)
            cout << " -- is a mirrored string.\n\n";
        else
            cout << " -- is a mirrored palindrome.\n\n";
    }

    return 0;
}