#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Res
{
    int a, b;
    bool operator < (const Res& other) const
    {
        return (abs(this->a - this->b)) < (abs(other.a - other.b));
    }
};

int main()
{
    int n, temp, target;
    unordered_map<int, int> table;
    vector<int> nums;
    vector<Res> resVec;
    while (scanf("%d", &n) != EOF)
    {
        table.clear();
        nums.clear();
        resVec.clear();
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &temp);
            nums.push_back(temp);
        }
        scanf("%d", &target);
        for (int num: nums)
        {
            if (table.find(num) != table.end())
            {
                resVec.push_back({target - num, num});
            }
            else
                table[target - num] = num;
        }
        sort(resVec.begin(), resVec.end());
        int a = resVec[0].a, b = resVec[0].b;
        printf("Peter should buy books whose prices are %d and %d.\n\n", min(a, b), max(a, b));
    }
    return 0;
}