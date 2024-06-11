#include <cstdio>

/*
    找遞迴關係式後直接遞迴即可

    看推導1.png
    最簡單可以觀察到第k個小時後全部的紅球數 = 3^k

    看推導2.png
    也可以很簡單的發現第k個小時後氣球Box的長寬都等於2^k

    看推導3.png
    依照題意也能找到在第k小時，將氣球Box經水平垂直的均分後可得4小塊
    其中只有右下角那塊都是藍氣球，其餘三塊是第k - 1小時copy過來的

    這題的遞迴式概念來自prefix sum
    define F(k, i): 在第k小時氣球Box中從row 1(最上層)到row i的紅球總數
    因此，第k小時氣球Box中row A ~ row B的紅球總數 = F(k, B) - F(k, A - 1)
    基本與prefix sum相同

    F(k, i)的遞迴關係式:
        case 1:
            if i = 0 時依照F的定義當然是 0，所以return 0
        case 2:
            if i != 0 && k = 0 時就是邊界初始條件1個紅球，所以return 1
        case 3:
            看堆導4.png
            當i <= 2^(k - 1)時代表此時row i在第k小時的上半部
            由於上半部的兩小塊是第k - 1小時的copy，
            所以要求F(k, i) [row i在上半部] 
            相當於求2倍的第k - 1小時的row i以上所有紅球數
            所以return 2 * F(k - 1, i)
        case 4:
            看推導5.png
            當i > 2^(k - 1)時代表row i在第k小時的下半部
            此時row i以上的紅球範圍包含了不完整的左下角那塊 + 兩個完整的小塊
            由於第三個觀察我們發現上半部的兩小塊是第k - 1小時的氣球Box的copy
            由第一個觀察又發現完整的一小塊是第k - 1小時的氣球Box
            第k - 1小時的氣球Box紅球共有3^(k - 1)顆
            剩下左下角不完整的小塊要處理
            用遞迴的想法可以發現由於row i在第k小時的下半部，
            又上半部已經處理完了，所以剩下沒算的紅球總數為
            (row i以上紅球總和) - 2 * (3 ^ (k - 1))
            相當於F(k - 1, i - 2^(k - 1))
            其中i - 2^(k - 1)的意思為在下半部中距離水平線的row數
            由於左下角那塊是第k - 1小時的copy，所以遞迴下去討論
            return F(k - , i - 2^(k - 1)) + 2 * 3^(k - 1)

    至此推完所有的關係式(整理在堆導6.png)
    程式直接做遞迴求答案即可
    最後答案為F(k, b) - F(k, a - 1)

    ps: 應該不能建任何的表，A、B的範圍到2^30，陣列會爆
*/

long long pow2[31];
long long pow3[31];

long long f(long long k, long long i)
{
    if (i == 0)
        return 0;
    if (k == 0)
        return 1;
    long long half = pow2[k - 1];
    if (i <= half)
        return 2 * f(k - 1, i);
    return f(k - 1, i - half) + 2 * pow3[k - 1];
}

int main()
{
    pow2[0] = 1;
    pow3[0] = 1;
    for (int i = 1; i < 31; ++i)
    {
        pow2[i] = pow2[i - 1] * 2;
        pow3[i] = pow3[i - 1] * 3;
    }

    long long k, a, b;
    int t;
    scanf("%d", &t);
    for (int Case = 1; Case <= t; ++Case)
    {
        scanf("%lld %lld %lld", &k, &a, &b);
        printf("Case %d: %lld\n", Case, f(k, b) - f(k, a - 1));
    }
    return 0;
}