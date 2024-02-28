#include <iostream>
#include <cstring>
using namespace std;

//純BigInt相加

char aDigits[1000005], bDigits[1000005];
int ans[1000005];
int ansSize = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    bool first = true;
    while (t--)
    {
        int n;
        cin >> n;
        memset(ans, 0, sizeof(ans));
        ansSize = 0;
        int a, b;
        int carry = 0;
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            cin >> aDigits[i] >> bDigits[i];
        }

        for (int i = n - 1; i >= 0; --i)
        {
            sum = (aDigits[i] - '0') + (bDigits[i] - '0') + carry;
            carry = sum / 10;
            sum %= 10;
            ans[ansSize++] = sum;
        }

        if (carry != 0)
            ans[ansSize++] = carry;
    
        if (first)
            first = false;
        else
            puts("");

        for (int i = ansSize - 1; i >= 0; --i)
            printf("%d", ans[i]);

        puts("");
    }
    return 0;
}