#include <bits/stdc++.h>
using namespace std;

#define maxn 300005
#define MOD 20071027

int trie[4005 * 105][30];
bool isWord[4005 * 105]; // 該節點是不是字串結尾

/*
    dp[i] -> i ~ n有幾種組合方式

    計算轉移式的概念是
    從後面開始枚舉i的時候
    再枚舉i ~ n之間的j
    此時如果i ~ j是一個題目給的pattern
    那麼dp[i] += dp[j + 1]
    也就是i ~ j的pattern一種方法 乘上 dp[j + 1] (也就是 j + 1 ~ n有幾種組法)
    為了快速找有沒有i ~ j的pattern
    需要用trie加速
*/

long long dp[maxn];

// trie的節點編號
int trieID = 1;

void insert(string& str)
{
    int curr = 1;
    for (char ch: str)
    {
        char c = ch - 'a';
        if (trie[curr][c] == 0)
        {
            trie[curr][c] = ++trieID;
        }
        curr = trie[curr][c];
    }
    isWord[curr] = true;
}

// 利用trie，可以一次找完 i ~ n 的組合方式
long long query(string& str, int i)
{
    long long cnt = 0;
    int curr = 1;
    for (int j = i; j < str.size(); ++j)
    {
        char c = str[j] - 'a';

        if (trie[curr][c] == 0)
            break;
        curr = trie[curr][c];
        
        // 是一個pattern的結尾，就有了一種可能的切法
        if (isWord[curr])
        {
            cnt += dp[j + 1];
            cnt %= MOD;
        }
    }

    return cnt;
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    int testcase = 0;

    string s;
    while (cin >> s)
    {
        memset(dp, 0, sizeof(dp));
        memset(trie, 0, sizeof(trie));
        memset(isWord, 0, sizeof(isWord));

        trieID = 1;

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i)
        {
            string pattern;
            cin >> pattern;
            insert(pattern);
        }

        int m = s.size();

        // dp邊界狀態
        dp[m] = 1;
        // 從後面開始枚舉i
        for (int i = m - 1; i >= 0; --i)
        {
            // 利用trie計算dp
            dp[i] += query(s, i);
            dp[i] %= MOD;
        }

        printf("Case %d: ", ++testcase);
        printf("%lld\n", dp[0]);
    }

    return 0;
}

/*
abcd
4
a
b
cd
ab
*/