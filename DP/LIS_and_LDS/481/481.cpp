#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
LIS(O(nlogn)) + 打印LIS

打印LIS用每一次更新LIS時去紀錄他的pos
currPos = LIS.len - 1
再從輸入倒過來找第一個pos[i] == currPos(之後currPos -= 1)
丟入vector or stack再讓輸出倒過來即可
*/

vector<int> LIS;
vector<int> seq;
vector<int> pos;
vector<int> ans;

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
        seq.emplace_back(n);
    
    pos.assign(seq.size() + 5, 0);

    LIS.emplace_back(seq[0]);
    pos[0] = 0;

    for (int i = 1; i < seq.size(); ++i)
    {
        if (LIS.back() < seq[i])
        {
            pos[i] = LIS.size();
            LIS.emplace_back(seq[i]);
        }
        else
        {
            auto it = lower_bound(LIS.begin(), LIS.end(), seq[i]);
            pos[i] = it - LIS.begin();
            *it = seq[i];
        }
    }

    printf("%d\n-\n", LIS.size());
    
    int currPos = LIS.size() - 1;
    for (int i = seq.size() - 1; i >= 0; --i)
    {
        if (currPos == pos[i])
        {
            ans.emplace_back(seq[i]);
            --currPos;
        }
    }

    for (int i = ans.size() - 1; i >= 0; --i)
        printf("%d\n", ans[i]);

    return 0;
}