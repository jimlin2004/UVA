#include <bits/stdc++.h>
using namespace std;

// AC自動機 + dp算機率

const int sigmaSize = 62 + 5; // a...z, A...Z, 0..9，多開5格
const int maxNode = 25 * 25 + 5;

// 用來編碼字元對應的數字，主要是因為ascii不好用
int idx[256];
double prob[sigmaSize]; // 字元的機率

int trie[maxNode][sigmaSize];
int fail[maxNode];
bool match[maxNode];
int trieNum;


void init()
{
    trieNum = 1;
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(match, 0, sizeof(match));
}


void insert(char* s)
{
    int m = strlen(s);

    int curr = 0;

    for (int i = 0; i < m; ++i)
    {
        int c = idx[s[i]];

        if (!trie[curr][c])
            trie[curr][c] = trieNum++;
        
        curr = trie[curr][c];
    }

    match[curr] = true;
}


void getFail()
{
    queue<int> q;
    
    fail[0] = 0;
    // root的小孩
    for (int c = 0; c < sigmaSize; ++c)
    {
        int v = trie[0][c];

        if (v)
        {
            fail[v] = 0; // 指向root
            q.push(v);
        }
    }

    // 建立fail
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int c = 0; c < sigmaSize; ++c)
        {
            int v = trie[u][c];

            if (!v) // 不存在
            {
                // 路徑壓縮
                trie[u][c] = trie[fail[u]][c];
                continue;
            }

            q.push(v);

            // 一路跳fail的鍊，直到找到一個節點可以接c
            int k = fail[u];
            while (k && !trie[k][c])
                k = fail[k];
            fail[v] = trie[k][c];
            // 當前字串包含著在fail[v]，所以如果fail[v]是禁止出現的，
            // 則v也是不行的(包含pattern)
            match[v] |= match[fail[v]];
        }
    }
}

// dp[u][len] -> 在trie的節點u中，還需要創造len個字的機率
double dp[maxNode][105];
bool vis[maxNode][105]; // dp是否算過
int K, N;

double getProb(int u, int len)
{
    if (len == 0)
        return 1.0;
    if (vis[u][len])
        return dp[u][len];
    
    vis[u][len] = true;

    double res = 0;
    for (int i = 0; i < N; ++i) // 枚舉每一種字
    {
        // 如果已經包含禁止出現的pattern，則機率為0
        // 所以這裡只加上沒有出現的機率
        if (!match[trie[u][i]])
            res += prob[i] * getProb(trie[u][i], len - 1);
    }

    return dp[u][len] = res;
}


int main()
{
    int testcase = 0;

    char pattern[25][25];

    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d", &K);

        for (int i = 0; i < K; ++i)
        {
            scanf("%s", &pattern[i]);
        }

        scanf("%d", &N);

        for (int i = 0; i < N; ++i)
        {
            char c;
            scanf(" %c %lf", &c, &prob[i]);
            idx[c] = i;
        }

        init();

        for (int i = 0; i < K; ++i)
        {
            insert(pattern[i]);
        }

        getFail();

        int len;
        scanf("%d", &len);

        memset(vis, 0, sizeof(vis));
        memset(dp, 0, sizeof(dp));

        printf("Case #%d: %.6lf\n", ++testcase, getProb(0, len));
    }

    return 0;
}