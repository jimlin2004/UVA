#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
簡單sort題，但問題是題目又不講輸入的數量QAQ
*/

struct Item
{
    int priority;
    string data;
    bool operator < (const Item& other) const
    {
        return this->priority < other.priority;
    }
};

vector<int> prioritys;
vector<Item> vec;

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    string input;
    stringstream ss;
    bool first = true;
    while (t--)
    {
        cin.ignore(); // for \n
        // cin.ignore(); // for \n
        ss.clear();
        vec.clear();
        prioritys.clear();

        getline(cin, input);

        ss << input;
        int priority;
        int count = 0;
        while (ss >> priority)
        {
            prioritys.emplace_back(priority);
            ++count;
        }

        string data;

        for (int i = 0; i < count; ++i)
        {
            cin >> data;
            vec.push_back({prioritys[i], data});
        }
        cin.ignore();

        sort(vec.begin(), vec.end());

        if (first)
            first = false;
        else
            cout << '\n';
        for (Item& item: vec)
        {
            cout << item.data << '\n';
        }
    }
    return 0;
}