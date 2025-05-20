#include <bits/stdc++.h>
using namespace std;

/*
    簡單題
    可以用算的利用公式與計數O(n)解決
    以下用模擬的O(n ^ 2)

    因為只有0 -> 1的操作
    所以可以簡單發現要改變1錯位的情況只能透過與0錯位的交換

    同時交換只算一步
    所以簡單的知道首先要先處理1錯位的
    1. 優先與0錯位的交換
    2. 用s[j] = '?'且t[j] = '1'的交換，這需要兩步

    剩下的0錯位可以直接換成1
    ?也能直接換成對應的字元

    最後再檢查一下是否有人還是錯位
*/

string str;
string targetStr;

int main()
{
    int T;
    cin >> T;

    int Case = 0;

    while (T--)
    {
        cin >> str;
        cin >> targetStr;

        int res = 0;

        // 優先用1錯位與0錯位交換
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == '1' && targetStr[i] == '0')
            {
                for (int j = 0; j < str.size(); ++j)
                {
                    if (str[j] == '0' && targetStr[j] == '1')
                    {
                        ++res;
                        swap(str[i], str[j]);
                        break;
                    }
                }
            }
        }

        // 用s[j] == '?' 且 t[j] == '1'去交換
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == '1' && targetStr[i] == '0')
            {
                for (int j = 0; j < str.size(); ++j)
                {
                    if (str[j] == '?' && targetStr[j] == '1')
                    {
                        res += 2;
                        str[j] = '0';
                        swap(str[i], str[j]);
                        break;
                    }
                }
            }
        }

        // 直接0變1
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == '0' && targetStr[i] == '1')
            {
                ++res;
                str[i] = '1';
            }
        }

        // 剩餘?直接變
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == '?')
            {
                ++res;
                str[i] = targetStr[i];
            }
        }

        // 是否有人還是錯位
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] != targetStr[i])
            {
                res = -1;
                break;
            }
        }

        printf("Case %d: %d\n", ++Case, res);

    }

    return 0;
}