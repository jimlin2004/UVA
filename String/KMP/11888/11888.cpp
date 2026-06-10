#include <bits/stdc++.h>
using namespace std;

/*
    如果一個S是alindrome，則
    S = AB，其中A、B都是迴文

    S^R = (AB)^R = (B^R)(A^R) = BA <- S的循環位移

    所以得到
    一個字串 S 如果是alindrome iff S^R是S的循環位移

    另外因為SS = ABAB
    所以SS = A(S^R)B

    因此如果能在SS中找到S^R，那S就是alindrome

    為了加速搜尋，使用KMP搜尋
    另外KMP有小改版(看下方)
*/

const int maxn = 200005;

string s;
string sr;
string ss;

// 失配函數
int f[maxn];

void buildF(const string& pattern)
{
    int len = pattern.size();
    f[0] = 0;
    for (int i = 1; i < len; ++i)
    {
        int j = f[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
            j = f[j - 1];
        if (pattern[i] == pattern[j])
            ++j;
        f[i] = j;
    }
}

int KMP(const string& text, const string& pattern)
{
    int j = 0;
    int matchPos = -1;
    for (int i = 0; i < text.size(); ++i)
    {
        while (j > 0 && text[i] != pattern[j])
            j = f[j - 1];
        if (text[i] == pattern[j])
            ++j;
        if (j == pattern.size())
        {
            matchPos = i - j + 1;
            /*
                為了判斷aaa這種既是迴文也是alindrome的
                第一次匹配時會在matchPos = 0的地方
                然後要繼續配後面看能不能在中間找到S^R
            */
            if (matchPos != 0)
                return matchPos;
            j = f[j - 1]; // 當作沒有，繼續搜尋
        }
    }

    return matchPos;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> s;
        ss = s + s;
        sr = s;
        reverse(sr.begin(), sr.end());

        buildF(sr);

        int matchPos = KMP(ss, sr);

        // 開頭或後半段
        if (matchPos == 0 || matchPos == sr.size())
            cout << "palindrome\n";
        else if (matchPos != -1)
            cout << "alindrome\n";
        else
            cout << "simple\n";
    }

    return 0;
}