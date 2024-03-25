#include <iostream>
#include <algorithm>
using namespace std;

// KMP

/*
例如: ababab -> next[] = {0, 0, 1, 2, 3, 4}
len = len(ababab)
repeatLen = len - next[len - 1] 得到的就是不在最長前後綴的長度
即前面的ab部分
再去檢查len % repeatLen有沒有== 0
有的話才會代表可以一直重複
*/

#define maxn 85

int nextFunc[maxn];

void buildNext(const string& s)
{
    int len = s.size();
    nextFunc[0] = 0;
    for (int i = 1; i < len; ++i)
    {
        int j = nextFunc[i - 1];
        while (j > 0 && s[i] != s[j])
            j = nextFunc[j - 1];
        if (s[i] == s[j])
            ++j;
        nextFunc[i] = j;
    }
}

int main()
{
    int t;
    cin >> t;
    bool first = true;
    while (t--)
    {
        string input;
        cin >> input;
        buildNext(input);
        int repeatLen = input.size() - nextFunc[input.size() - 1];
        if (input.size() % repeatLen != 0)
            repeatLen = input.size();
        if (first)
            first = false;
        else
            cout << '\n';
        cout << repeatLen << '\n';
    }
    return 0;
}