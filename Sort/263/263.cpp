#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main()
{
    int originN;
    while (scanf("%d", &originN) && originN)
    {
        printf("Original number was %d\n", originN);
        unordered_map<int, bool> mp;
        vector<int> l, r;
        int lNum, rNum;
        int curr = originN;
        int count = 0;
        while (mp.find(curr) == mp.end())
        {
            l.clear();
            r.clear();
            int remain = curr;
            while (remain)
            {
                l.emplace_back(remain % 10);
                r.emplace_back(remain % 10);
                remain /= 10;
            }

            sort(l.begin(), l.end(), greater<int>());
            sort(r.begin(), r.end(), less<int>());

            lNum = rNum = 0;
            for (int num: l)
                lNum = lNum * 10 + num;
            for (int num: r)
                rNum = rNum * 10 + num;
            
            //第一次的curr不應該紀錄
            if (count != 0)
                mp.insert({curr, true});
            curr = lNum - rNum;

            printf("%d - %d = %d\n", lNum, rNum, curr);
            ++count;
        }
        printf("Chain length %d\n\n", count);
    }
    return 0;
}