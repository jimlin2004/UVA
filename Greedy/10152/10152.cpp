#include <bits/stdc++.h>
using namespace std;


/*

    稍微想一下就能知道的題目
    由於烏龜要排序時就要爬到最上面
    其他烏龜會掉下去
    所以作法很簡單
    只要底部用O(n)的檢查錯位的有哪些烏龜，用bool error[]紀錄
    (以下數字是指想要的順序中烏龜的index)
    此時從錯位中數字最大的烏龜開始搬移一定是最優解
    因為烏龜只能到最上面去，所以數字最大的一定要先動，否則會多步數

    可以用下方舉例看出做法(數字是用"想要"得來的)
    (x)代表錯位，錯位可以簡單用O(n)得到
    原始                         想要
    1: Yertle             (x)    1: Yertle
    4: Duke of Earl              2: Richard M. Nixon
    3: Sir Lancelot       (x)    3: Sir Lancelot
    5: Elizabeth Windsor         4: Duke of Earl
    6: Michael Eisner            5: Elizabeth Windsor
    2: Richard M. Nixon   (x)    6: Michael Eisner
    7: Mr. Rogers                7: Mr. Rogers
    8: Ford Perfect              8: Ford Perfect
    9: Mack                      9: Mack

*/


// 用來轉換烏龜名與數字
unordered_map<string, int> mp;

int turtles[205];
// 數字轉烏龜名
string numberToName[205];
// 是否該烏龜的順序有錯
bool error[205];
// 原始輸入
string ori[205];

int main()
{
    int T;
    cin >> T;

    bool first = true;
    while (T--)
    {
        mp.clear();

        int n;
        cin >> n;

        cin.ignore();

        for (int i = 1; i <= n; ++i)
        {
            string name;
            getline(cin, name);
            ori[i] = name;
        }

        for (int i = 1; i <= n; ++i)
        {
            string name;
            getline(cin, name);
            mp[name] = i;
            numberToName[i] = name;
        }

        // 得到原始順序烏龜的編號
        for (int i = 1; i <= n; ++i)
        {
            turtles[i] = mp[ori[i]];
        }

        // O(n)找錯位烏龜
        int target = n;
        for (int i = n; i >= 1; --i)
        {
            if (turtles[i] == target)
            {
                --target;
                error[turtles[i]] = false;
            }  
            else
            {
                error[turtles[i]] = true;
            }
        }

        // 從最大的開始輸出
        for (int i = n; i >= 1; --i)
        {
            if (error[i])
                cout << numberToName[i] << '\n';
        }
        cout << '\n';
    }

    return 0;
}

/*
4
3
Yertle
Duke of Earl
Sir Lancelot
Duke of Earl
Yertle
Sir Lancelot
9
Yertle
Duke of Earl
Sir Lancelot
Elizabeth Windsor
Michael Eisner
Richard M. Nixon
Mr. Rogers
Ford Perfect
Mack
Yertle
Richard M. Nixon
Sir Lancelot
Duke of Earl
Elizabeth Windsor
Michael Eisner
Mr. Rogers
Ford Perfect
Mack
7
Yertle
Oscar
Baron
Lord
King
White
Kong
Oscar
Baron
Lord
Yertle
King
Kong
White
3
Yertle
Duke of Earl
Sir Lancelot
Yertle
Duke of Earl
Sir Lancelot

*/