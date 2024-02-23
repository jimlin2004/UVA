#include <iostream>
using namespace std;

/*
這是考組合數的題目
len = 1的字串有C(26, 1)個
len = 2的字串有C(26, 2)個
len = 3的字串有C(26, 3)的
...
Why: <重點>嚴格上升
    因為假設len = 3 -> C(26, 3)會選出不重複的3個字母，C不考慮排列，
    所以選出的3個字母(由於不重複)可以相當於count出所有len = 3且排序的個數(只有一種排列方式)

再來假設今天要算ceh，Ans = 0
由於len = 3 -> 先加上len = 2與len = 1的個數 Ans += (C(26, 1) + C(26, 2))
Why:
    如此長度才會是3開始
    就跟進位一樣，假設今天是3位數字(123)，勢必會需要先算過2位數字，1位數字的個數
    開始算第3位數時就跟新的循環一樣，that is 0 ~ 99(2位數個數)要算一遍，在從100~123開始算
回到ceh
先看第1位c，在c**的前面會需要算過a**，b**(不能到達c**，否則C(n, k)得到的字串可能 > cef)，
所以Ans += (a**) + (b**) -> Ans += (C(25, 2) + C(24, 2))
再來第2位e，但不能是ca*(因為要嚴格遞增)，所以要從前一位的字母的下一開始(that is 'd')，
符合的只有cd* -> Ans += (cd*) -> Ans += C(22, 1)
最後一位h
有cef, ceg 2個 -> Ans += 2，如此得到的就是ceg的word index

最後只要Ans += 1即為答案(ceh的word index)

總結: Ans = C(26, 2) + C(26, 1) + C(25, 2) + C(24, 2) + C(22, 1) + 2 + 1
*/

/* <注> 這題可以暴力的用map一個個字串映射，也會過 */

//最大用到C[n][k] -> n <= 26, k <= 5
//k開到30是方便巴斯卡三角的運算
//不然就是要for loop中特別處理min...
int C[30][30];

void solve(const string& word)
{
    int len = word.size();
    //檢查字串是否嚴格上升
    for (int i = 1; i < len; ++i)
    {
        if (word[i] <= word[i - 1])
        {
            puts("0");
            return;
        }
    }

    int res = 0;
    //先加上長度短的總數
    for (int i = 1; i < len; ++i)
        res += C[26][i];
    
    char startFrom = 'a';
    for (int i = 0; i < len; ++i)
    {
        for (; startFrom < word[i]; ++startFrom)
        {
            //C[n][0]會是在最後一位字母的時候+1+1慢慢加，直到n >= 最後一位字母
            res += C['z' - startFrom][len - i - 1];
        }
        //上一位的下一位
        ++startFrom;
    }
    printf("%d\n", res + 1);
}

int main()
{
    //巴斯卡三角形
    for (int i = 0; i <= 26; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
        {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }

    string word;
    while (cin >> word)
    {
        solve(word);
    }
    return 0;
}