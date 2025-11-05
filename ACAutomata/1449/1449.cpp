#include <bits/stdc++.h>
using namespace std;

// AC自動機的節點
/*
    v的fail指標指向u，且v是u的最長後綴
    v的last指標指向第一個有輸出的u
*/
struct Node
{
    int child[26];
    int fail;
    int last;
    vector<int> patternIDs; // 以這個節點為結束的patternID

    Node()
    {
        memset(child, -1, sizeof(child));
        fail = 0; // 預設指向root
        last = 0; // 預設指向root
    }
};

class AC
{
private:
    vector<Node> trie;
public:
    AC()
    {
        this->init();
    }

    void init()
    {
        trie.clear();
        trie.emplace_back(); // 放一個root id = 0
    }

    void insert(const string& s, int id)
    {
        int curr = 0;
        for (char c: s)
        {
            int ch = c - 'a';
            if (trie[curr].child[ch] == -1) // node還沒開
            {
                trie[curr].child[ch] = trie.size();
                trie.emplace_back();
            }
            curr = trie[curr].child[ch];
        }
        trie[curr].patternIDs.emplace_back(id); // 尾巴紀錄是一個pattern的結尾
    }

    // 用BFS建立fail與last
    void build()
    {
        queue<int> q;
        // root的小孩額外處理
        for (int ch = 0; ch < 26; ++ch)
        {
            int v = trie[0].child[ch];
            if (v != -1) // 子節點有人
            {
                trie[v].fail = 0; // 指向root
                trie[v].last = 0; // 指向root
                q.push(v);
            }
            else
            {
                trie[0].child[ch] = 0; //該節點不存在就指向root，做路徑壓縮
            }
        }

        // 開始BFS
        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int ch = 0; ch < 26; ++ch)
            {
                int v = trie[u].child[ch];

                if (v != -1)
                {
                    trie[v].fail = trie[trie[u].fail].child[ch];

                    //last優化
                    if (!trie[trie[v].fail].patternIDs.empty()) // v的fail有輸出
                        trie[v].last = trie[v].fail;
                    else
                        trie[v].last = trie[trie[v].fail].last; // v的fail沒輸出 -> 鍊上最近有輸出的是v的fail的last
                    
                    q.push(v);
                }
                else
                {
                    // 沒有邊就指向fail[u]的邊，做路徑壓縮
                    trie[u].child[ch] = trie[trie[u].fail].child[ch];
                }
            }
        }
    }

    void query(const string& text, vector<int>& cnt)
    {
        int u = 0;
        for (int i = 0; i < text.size(); ++i)
        {
            int ch = text[i] - 'a';
            u = trie[u].child[ch];

            // 自己這個點的pattern
            for (int id: trie[u].patternIDs)
                ++cnt[id];
            // 用last往回跳鍊
            for (int fail = trie[u].last; fail != 0; fail = trie[fail].last)
            {
                for (int id: trie[fail].patternIDs)
                    ++cnt[id];
            }
        }
    }
};


vector<string> patterns;
AC ac;

void init()
{
    ac.init();
    patterns.clear();
}


int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        init();

        string pattern;
        for (int i = 0; i < n; ++i)
        {
            cin >> pattern;
            patterns.emplace_back(pattern);
            ac.insert(pattern, i);
        }

        ac.build();

        string text;
        cin >> text;

        vector<int> cnt(patterns.size(), 0);
        ac.query(text, cnt);

        int maxCnt = *max_element(cnt.begin(), cnt.end());

        cout << maxCnt << '\n';
        for (int i = 0; i < cnt.size(); ++i)
        {
            if (cnt[i] == maxCnt)
            {
                cout << patterns[i] << '\n';
            }
        }
    }

    return 0;
}