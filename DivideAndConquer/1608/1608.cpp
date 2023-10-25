#include <cstdio>
#include <map>
using namespace std;

int n;
int nums[200005];
int l[200005]; //自左邊過來第一個與自己數字相同的index
int r[200005]; //自右邊過來第一個與自己數字相同的index
//若找不到與自己相同的則左端點標記為-1，右端點標記為n + 1
map<int, int> mp;//map<數字，出現位置>，左右array共用

//檢查(left, right)中是否有unique的數字
//unique的檢查法:
//  當left > l[i] && right < r[i]時即為unique
//用分治的方式檢查每個區間
//經測試，一定要left與right同時逼近，否則time limit
bool check(int left, int right) 
{
    if (left == right - 1)
        return true;
    int i = left + 1, j = right - 1;
    while (i <= j)
    {
        if (left >= l[i] && right <= r[i])
            return check(left, i) && check(i, right);
        if (left >= l[j] && right <= r[j])
            return check(left, j) && check(j, right);
        i++, j--;
    }
    return false;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &nums[i]);
        }
        mp.clear();

        for (int i = 0; i < n; ++i)
        {
            if (mp.count(nums[i]) != 0)
            {
                l[i] = mp[nums[i]];
                mp[nums[i]] = i;
            }
            else
            {
                l[i] = -1;
                mp[nums[i]] = i;
            }
        }

        mp.clear();

        for (int i = n - 1; i >= 0; --i)
        {
            if (mp.count(nums[i]) != 0)
            {
                r[i] = mp[nums[i]];
                mp[nums[i]] = i;
            }
            else
            {
                r[i] = n;
                mp[nums[i]] = i;
            }
        }

        puts((check(-1,n)) ? "non-boring" : "boring");
    }
    return 0;
}