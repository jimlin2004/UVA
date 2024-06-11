#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
    就暴力把字拆開
    然後用unordered_map去看有沒有出現過
*/

unordered_map<string, bool> mp;
vector<string> vec;

int main()
{
    string str;
    while (cin >> str)
    {
        mp.insert({str, true});
        vec.emplace_back(str);
    }

    for (const string& s: vec)
    {
        for (int i = 1; i < s.size(); ++i)
        {
            string s1 = s.substr(0, i);
            string s2 = s.substr(i, s.size() - i);
            if ((mp.find(s1) != mp.end()) && (mp.find(s2) != mp.end()))
            {
                cout << s << '\n';
                break;
            }
        }
    }
    return 0;
}