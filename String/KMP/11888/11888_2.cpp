#include <bits/stdc++.h>
using namespace std;

/*
    版本一的方法可以用於這一題字串只由兩個迴文結合的情況
    這裡使用更泛用的KMP技巧
    找出字串所有的迴文前綴與迴文後綴

    原字串S，想知道S的前綴是不是迴文
    如果S的某個前綴是迴文，那這一段迴文會出現在S^R的後綴

    為了用KMP找出來，建構
    T = S + $ + S^R ($是用來避免KMP有overlap)

    當用KMP算出失配函數f[]的時候，
    f[|T| - 1]的意思是T中最長相等前後綴長度
    由於T = S + $ + S^R 
    所以f[|T| - 1]的意義也是S中最長的迴文前綴長度

    同時也可以用f[]去跳鍊，找出所有迴文前綴
    len = f[|T| - 1]是最長迴文前綴
    其次長的就是len = f[len - 1]直到len == 0

    過程中可以將len記在isPrefixPalindrome[len] = true中

    然後反過來創造
    T = S^R + $ + S
    就能得到後綴迴文
    isSuffixPalindrome[len] = true中

    最後用for loop O(N)枚舉所有切割長度就行了
*/

const int maxn = 400005;

string s;
string sr;
string T1;
string T2;
bool isPrefixPalindrome[maxn];
bool isSuffixPalindrome[maxn];

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

void KMP_to_get_prefix_palindrome(const string& text, bool isPalindromeArr[])
{
    memset(isPalindromeArr, 0, text.size() * sizeof(bool));
    buildF(text);

    // 開始跳鍊找出所有前綴迴文
    int len = f[text.size() - 1];
    while (len != 0)
    {
        isPalindromeArr[len] = true;
        len = f[len - 1];
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> s;
        sr = s;
        reverse(sr.begin(), sr.end());

        T1 = s + '$' + sr;
        T2 = sr + '$' + s;

        KMP_to_get_prefix_palindrome(T1, isPrefixPalindrome);
        KMP_to_get_prefix_palindrome(T2, isSuffixPalindrome);

        bool isAlindrome = false;

        // 枚舉所有長度切點
        for (int len = 1; len < s.size(); ++len)
        {
            // 前綴(前段)、後綴(後段)都是迴文
            if (isPrefixPalindrome[len] && isSuffixPalindrome[s.size() - len])
            {
                isAlindrome = true;
                break;
            };
        }

        if (isAlindrome)
            cout << "alindrome\n";
        else if (isPrefixPalindrome[s.size()])
        {
            // 如果isPrefixPalindrome[s.size()]如果是true，
            // 那前綴(就是整個s)就是迴文
            cout << "palindrome\n";
        } 
        else
            cout << "simple\n";
    }

    return 0;
}