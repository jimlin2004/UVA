#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    map<int, vector<string>> tabel;
    int n;
    cin >> n;
    string str;
    int priority;
    map<int, vector<string>>::iterator it;
    for (int i = 1; i <= n; i++)
    {
        tabel.clear();
        for (int j = 0; j < 10; j++)
        {
            cin >> str >> priority;
            if (tabel.find(priority) != tabel.end())
            {
                tabel[priority].push_back(str);
            }
            tabel.insert({priority, {str}});
        }
        cout << "Case #" << i << ":\n";
        it = tabel.end();
        it--;
        for (string s: it->second)
            cout << s << '\n';
    }
    return 0;
}