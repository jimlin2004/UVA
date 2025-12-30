#include <bits/stdc++.h>
using namespace std;

/*
    題意:
        給定N, L, U
        找L <= M <= U中 N | M可以得到最大值的M
        若有多個M則取最小的M

    貪婪
    首先要讓 N | M 要最大
    那麼優先考慮讓越多most significant bit變成1

    所以從bits的左邊開始嘗試

    再來M要最小
    所以如果原本N的那個bit已經是1了，那M的那個bit能不要設定1最好
    但是如果不變成1 M會小於L，那就不得不變成1了

    同理雖然越多N的bit從0變1越好
    但是如果M的那個bit設成1會比U還大，那就不能設成1了
*/

int main()
{
    unsigned int N, L, U;
    while (scanf("%u %u %u", &N, &L, &U) != EOF)
    {
        unsigned int res = 0;
        for (int i = 31; i >= 0; --i)
        {
            unsigned int mask = 1 << i;
            if ((N & mask) == 0) // N的該bit是0
            {
                if ((res | mask) <= U) // M的該bit想設成1，要檢查會不會超過U
                    res |= mask;
            }
            else // N的該bit是1
            {
                if ((res | mask) <= L) // M的該bit如果設成1還是小於L，那就不得不設成1 
                    res |= mask;
            }
        }

        printf("%u\n", res);
    }

    return 0;
}