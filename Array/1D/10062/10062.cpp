#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

struct Item
{
    int c, f;
    bool operator < (const Item& other) const
    {
        if (this->f == other.f)
        {
            return this->c > other.c;
        }
        return this->f < other.f;
    }
};

//ascii
int table[260];
vector<Item> items;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    string input;
    bool first = true;
    while (getline(cin, input))
    {
        memset(table, 0, sizeof(table));
        items.clear();
        for (char c: input)
        {
            ++table[c];
        }

        for (int i = 0; i < 260; ++i)
        {
            if (table[i] != 0)
            {
                items.emplace_back(Item{i, table[i]});
            }
        }

        sort(items.begin(), items.end());
        
        if (first)
            first = false;
        else
            cout << '\n';
        
        for (const Item& item: items)
        {
            cout << item.c << ' ' << item.f << '\n';
        }
    }
    return 0;
}