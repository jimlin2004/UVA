#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

/*
    題意就是找到最長不連續的子字串
    作法就是遇到重複的數值時把之前的數值照順序刪直到
    與現在重複的值被刪掉為止
    因為只要到之前重複的那個後面都是唯一的值
    可以繼續算
*/

map<int, bool> mp;

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        mp.clear();
        queue<int> q;
        int n;
        scanf("%d", &n);
        int num;
        int res = -1;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &num);
            if (mp.find(num) == mp.end())
                mp.insert({num, true});
            else
            {
                res = max(res, (int)mp.size());
                while (mp.find(num) != mp.end())
                {
                    mp.erase(q.front());
                    q.pop();
                } 
                mp.insert({num, true});
            }
            q.push(num);
        }
        res = max(res, (int)mp.size());
        printf("%d\n", res);
    }
    return 0;
}