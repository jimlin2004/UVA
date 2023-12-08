#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

int gcd(int a, int b)
{
    return (b == 0) ? (a) : (gcd(b, a % b));
}

int main()
{

    vector<int> nums;
    int t;

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> t;
    cin.ignore();
    while (t--)
    {
        int maxGCD = 1;
        nums.clear();
        string input;
        getline(cin, input);
        stringstream ss(input);
        string token;
        while (ss >> token)
        {
            nums.emplace_back(stoi(token));
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = i + 1; j < nums.size(); ++j)
            {
                maxGCD = max(maxGCD, gcd(nums[i], nums[j]));
            }
        }

        cout << maxGCD << '\n';
    }
    return 0;
}