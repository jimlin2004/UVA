#include <bits/stdc++.h>
using namespace std;

// 直接砸AC自動機

struct TrieNode
{
    int child[60];
    int fail;
    int last;
    vector<int> patternIDs;

    TrieNode()
    {
        memset(child, -1, sizeof(child));
        fail = 0;
        last = 0;
    }
};

int charToIndex[256];

class AC
{
public:
    vector<TrieNode> trie;

    void init()
    {
        trie.clear();
        trie.emplace_back(); // 放root
    }

    void insert(char* s, int id)
    {
        int n = strlen(s);

        int curr = 0;

        for (int i = 0; i < n; ++i)
        {
            int c = charToIndex[s[i]];
            if (trie[curr].child[c] == -1)
            {
                trie.emplace_back();
                trie[curr].child[c] = trie.size() - 1;
            }
            curr = trie[curr].child[c];
        }
        trie[curr].patternIDs.emplace_back(id);
    }

    void build()
    {
        queue<int> q;
        // root的小孩
        for (int c = 0; c < 60; ++c)
        {
            int v = trie[0].child[c];
            if (v != -1)
            {
                trie[v].fail = 0;
                trie[v].last = 0;
                q.push(v);
            }
            else
                trie[0].child[c] = 0; // 路徑壓縮
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int c = 0; c < 60; ++c)
            {
                int v = trie[u].child[c];
                if (v != -1)
                {
                    trie[v].fail = trie[trie[u].fail].child[c];

                    if (!trie[trie[v].fail].patternIDs.empty())
                        trie[v].last = trie[v].fail;
                    else
                        trie[v].last = trie[trie[v].fail].last;
                
                    q.push(v);
                }
                else
                {
                    trie[u].child[c] = trie[trie[u].fail].child[c];
                }
            }
        }
    }

    void search(char* s, vector<bool>& found)
    {
        int m = strlen(s);
        
        int curr = 0;
        for (int i = 0; i < m; ++i)
        {
            int c = charToIndex[s[i]];

            curr = trie[curr].child[c];

            // 一路跳鍊回去
            for (int fa = curr; fa != 0; fa = trie[fa].last)
            {
                for (int id: trie[fa].patternIDs)
                {
                    found[id] = true;
                }
            }
        }
    }
};

char text[100005];
char pattern[1005];
AC ac;

int main()
{
    int lastIndex = 0;
    for (char c = 'a'; c <= 'z'; ++c)
        charToIndex[c] = lastIndex++;

    for (char c = 'A'; c <= 'Z'; ++c)
        charToIndex[c] = lastIndex++;

    int T;
    scanf("%d", &T);
    while (T--)
    {
        ac.init();

        scanf("%s", &text);
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; ++i)
        {
            scanf("%s", &pattern);
            ac.insert(pattern, i);
        }

        ac.build();

        vector<bool> found(q, false);

        ac.search(text, found);

        for (int i = 0; i < q; ++i)
            puts((found[i]) ? "y" : "n");
    }

    return 0;
}