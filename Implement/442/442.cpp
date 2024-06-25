#include <iostream>
#include <stack>
#include <map>
#include <string>
using namespace std;

//注意: 這題()裡每次一定只有兩個matrix要計算

struct Mat
{
    int row, column;
};

map<char, Mat> mp;

int main()
{
    int n;
    cin >> n;
    char var;
    int row, col;
    for (int i = 0; i < n; ++i)
    {
        cin >> var >> row >> col;
        mp[var] = Mat{row, col};
    }

    cin.ignore();
    string line;
    while (getline(cin, line))
    {
        stack<Mat> sk;
        long long res = 0;
        bool isError = false;
        for (int i = 0; i < line.size(); ++i)
        {
            if (line[i] == '(')
                continue;
            if (line[i] != ')')
            {
                sk.push(mp[line[i]]);
                continue;
            }
            
            //到這裡代表讀到 ')'
            Mat b = sk.top();
            sk.pop();
            Mat a = sk.top();
            sk.pop();
            if (a.column != b.row)
            {
                isError = true;
                break;
            }

            res += a.row * b.row * b.column;
            sk.push({a.row, b.column});
        }

        if (isError)
            puts("error");
        else
            printf("%lld\n", res);
    }
    return 0;
}