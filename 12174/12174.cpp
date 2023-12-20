#include <cstdio>
#include <cstring>
using namespace std;

// #define maxn 100005
#define maxn 1005

//向前有沒有s個不同的數
bool vaildForward[maxn * 2];
//向後有沒有s個不同的數
bool vaildBackward[maxn * 2];
int count[maxn];
int history[maxn];

int solve(int s, int n)
{
    memset(count, 0, sizeof(count));
    memset(vaildForward, false, sizeof(vaildForward));
    memset(vaildBackward, false, sizeof(vaildBackward));

    //不一樣的數字個數
    int diffNum = 0;

    for (int i = 1; i <= s + n; ++i)
    {
        //左邊不完整
        if (i <= s)
        {
            if (count[history[i]] != 0)
            {
                ++count[history[i]];
                vaildForward[i] = false;
            }
            else
            {
                ++count[history[i]];
                ++diffNum;
                if (diffNum == i)
                    vaildForward[i] = true;
                else
                    vaildForward[i] = false;
            }
        }

        //中間
        if (s < i && i <= n)
        {
            --count[history[i - s]];
            if (count[history[i - s]] == 0)
                --diffNum;
            if (count[history[i]] == 0)
                ++diffNum;
            ++count[history[i]];
            if (diffNum == s)
            {
                vaildForward[i] = true;
                vaildBackward[i - s + 1] = true;
            }
        }

        //右邊不完整
        if (i > n)
        {
            --count[history[i - s]];
            if (count[history[i - s]] == 0)
                --diffNum;
            if (count[history[i - s]] <= 1 && diffNum > 0)
            {
                vaildBackward[i - s + 1] = true;
                vaildForward[i] = true;
            }
                
        }
    }
    
    int res = 0;
    bool ok;
    for (int i = 1; i <= n; ++i)
    {
        if (!vaildForward[i - 1])
            continue;
        ok = true;
        for (int j = i; j <= n && ok; j += s)
            if (!vaildBackward[j])
                ok = false;
        if (ok)
            ++res;
    }
    return res;
}

int main()
{
    int t;
    int s, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &s, &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &history[i]);
        }

        printf("%d\n", solve(s, n)); 
    }
    return 0;
}