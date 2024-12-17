#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
    一臉greedy題

    每個村莊可以視為一個點
    每個點可以用半徑D畫圓
    由於一定與高速公路(在x軸)有一定區間的相交
    因此題目就轉成在每個圓與x軸相交的區間中選最少的點可以涵蓋所有區間
    解法是將區間以右端點由小到大排
    curr = segments[0].to
    當cur < segments[i].from代表需要新的點
    此時更新curr = segments[i].to建立那個新的點

    每一次都選最右邊可以保證能夠包含最多的區間，所以貪心(可證)
*/

struct Segment
{
    long long from, to;
    bool operator < (const Segment& other) const
    {
        return this->to < other.to;
    }
};

vector<Segment> segments;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    long long L;
    while (cin >> L)
    {
        long long D;
        cin >> D;
        int n;
        cin >> n;
        segments.clear();
        for (int i = 0; i < n; ++i)
        {
            // (a, b)是村莊的位置，也就是圓心
            long long a, b;
            cin >> a >> b;
            // a +- sqrt(D * D - b * b)是用圓方程式與高速公路(y = 0)去解聯立解出來的
            // 另外這題的數字畫成整數，不需要小數點
            long long x1 = a - (long long)sqrt(D * D - b * b);
            long long x2 = a + (long long)sqrt(D * D - b * b);
            // 注意不要超出去高速公路的範圍
            segments.push_back({max(0LL, x1), min(x2, L)});
        }
        sort(segments.begin(), segments.end());
        long long curr = segments[0].to;
        int res = 1;
        for (Segment segment: segments)
        {
            if (curr < segment.from)
            {
                curr = segment.to;
                ++res;
            }
        }
        cout << res << '\n';
    }
    return 0;
}