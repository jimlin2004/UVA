#include <iostream>
#include <string>
using namespace std;

#define maxn 1000005

// KMP

/*
例如: ababab -> next[] = {0, 0, 1, 2, 3, 4}
len = len(ababab)
repeatLen = len - next[len - 1] 得到的就是不在最長前後綴的長度
即前面的ab部分
再去檢查len % repeatLen有沒有== 0
有的話才會代表可以一直重複
*/

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
    string str;
    while (cin >> str && str != ".")
    {
        buildNext(str);

        int len = str.size();
        int repeatLen = len - nextFunc[len - 1];
        if (len % repeatLen == 0)
            printf("%d\n", len / repeatLen);
        else
            puts("");
    }
    return 0;
}