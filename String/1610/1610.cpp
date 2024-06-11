#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
    簡單字串題
    將所有的string sorting
    取中間兩個為a, b
    string res = "";
    之後一直不斷的枚舉index i, res[i] = 'A'開始去看
    res 有沒有 >= a，否則該res[i]一直試試看 = 'B'、'C'、'D'...
    再檢查是否 res >= a && res < b
    就是答案了
    否則 i++ 繼續試下去
*/

vector<string> vec;

int main()
{
    int n;
    while (cin >> n && n)
    {
        vec.clear();
        string in;
        for (int i = 0; i < n; ++i)
        {
            cin >> in;
            vec.push_back(in);
        }

        sort(vec.begin(), vec.end());

        string a = vec[n / 2 - 1];
        string b = vec[n / 2];

        string res = "A";
        int index = 0;
        
        while (index < a.size())
        {
            while (res[index] <= 'Z' && res < a)
                ++res[index];
            if (res[index] <= 'Z' && (res >= a) && (res < b))
                break;
            if (res[index] != a[index])
                --res[index];
            res += 'A';
            ++index;
        }

        cout << res << '\n';
    }
    return 0;
}