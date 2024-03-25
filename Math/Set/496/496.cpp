#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

/*
照著set的數學定義做即可
*/

vector<int> set1;
vector<int> set2;

int countUnionSize()
{
    int count = 0;
    // int len = min(set1.size(), set2.size());
    int i = 0, j = 0;
    while ((i < set1.size()) && (j < set2.size()))
    {
        if (set1[i] == set2[j])
        {
            ++count;
            ++i;
            ++j;
        }
        else if (set1[i] > set2[j])
            ++j;
        else
            ++i;
    }
    return count;
}

int main()
{
    stringstream ss;
    string line;
    int n;
    while (getline(cin, line))
    {
        set1.clear();
        set2.clear();
        ss.clear();

        ss << line;
        while (ss >> n)
            set1.emplace_back(n);

        getline(cin, line);
        ss.clear();
        ss << line;
        while (ss >> n)
            set2.emplace_back(n);

        sort(set1.begin(), set1.end());
        sort(set2.begin(), set2.end());

        int unionCount = countUnionSize();
        //在A不在B
        int diffCountA = set1.size() - unionCount;
        //在B不在A
        int diffCountB = set2.size() - unionCount;

        if ((unionCount == set1.size()) && (unionCount == set2.size()))
        {
            cout << "A equals B" << '\n';
        }
        else if (unionCount == set1.size() && diffCountA == 0)
            cout << "A is a proper subset of B\n";
        else if (unionCount == set2.size() && diffCountB == 0)
            cout << "B is a proper subset of A\n";
        else if (unionCount == 0)
        {
            cout << "A and B are disjoint\n";
        }
        else
            cout << "I'm confused!\n";
    }
    return 0;
}