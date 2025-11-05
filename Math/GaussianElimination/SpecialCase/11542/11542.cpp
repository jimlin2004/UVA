#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
以 4 6 10 15為例
質因數分解:
     4 = 2 * 2
     6 = 2 * 3
    10 = 2 * 5
    15 = 3 * 5
    若以x_1代表選或不選4
    x_2代表選或不選6
    x_3代表選或不選10
    x_4代表選或不選15
    以此類推，x_1 、 x_2 、 x_3 、 x_4...只可能是 0 or 1
    也就是 (4**x_1) * (6**x_2) * (10**x_3) * (15**x_4) = (某一數)**2
    寫作 [(2 * 2)**x_1] [(2 * 3)**x_2] * [(2 * 5)**x_3] * [(3 * 5)**x_4] = (某一數)**2
    要是某一數的平方，質因數的指數必須是even
    也就是
    (2)的指數 2x_1 + x_2 + x_3 = even
    (3)的指數 x_2 + x_4 = even
    (5)的指數 x_3 + x_4 = even
    的聯立方程式
    亦可寫作
    x_2 + x_3 = 0 (mod 2)
    x_2 + x_4 = 0 (mod 2)
    x_3 + x_4 = 0 (mod 2)
    由於只有0 or 1
    所以變成解
    x_2 ^ x_3 = 0
    x_2 ^ x_4 = 0
    x_3 ^ x_4 = 0
    用高斯消去解決
        x_1 x_2 x_3 x_4         x_1 x_2 x_3 x_4         x_1 x_2 x_3 x_4
    2    0   1   1   0  | 0   2  0   1   1   0  | 0   2  0   1   1   0  | 0
    3    0   1   0   1  | 0 ~ 3  0   0   1   1  | 0 ~ 3  0   0   1   1  | 0
    5    0   0   1   1  | 0   5  0   0   1   1  | 0   5  0   0   0   0  | 0
    The matrix is in the echelon form，Free variables are x_1 and x_4
    定理
    number of Free variables
    = number of variables - rank = 4 - 2 = 2
    所以答案即為2**2 - 1 = 3 (-1 for 都不選的case)
*/

vector<int> primes;
bool isNotPrime[505];
int A[505][505];
int maxP;

//埃氏篩
void getPrimes()
{
    isNotPrime[0] = isNotPrime[1] = true;
    for (int i = 2; i <= 500; ++i)
    {
        if (!isNotPrime[i])
        {
            primes.emplace_back(i);
            for (int j = i * i; j <= 500; j += i)
            {
                isNotPrime[j] = true;
            }
        }
    }
}

int gaussian_elimination(int m, int n)
{
    // i -> 處理到第幾個row，j -> 處理到第幾個col
    int i, j, k, r;
    i = j = 0;
    while (i < m && j < n)
    {
        r = i;
        //找到起頭是1的row
        for (k = i; k < m; ++k)
        {
            if (A[k][j])
            {
                r = k;
                break;
            }
        }

        if (A[k][j])
        {
            //將起頭是1的row interchange到i-th row
            if (r != i)
            {
                for (k = 0; k < n; ++k)
                    swap(A[r][k], A[i][k]);
            }

            //進行高斯消去
            for (int u = i + 1; u < m; ++u)
            {
                // 將第i row往下消去其他row
                if (A[u][j])
                {
                    for (k = i; k < n; ++k)
                        A[u][k] ^= A[i][k];
                }
            }
            ++i; // 換下一個row
        }
        ++j; // 換下一個col
    }
    //free-variable數量
    return n - i;
}

int main()
{
    getPrimes();

    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(A, 0, sizeof(A));
        int n;
        long long x;
        maxP = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", &x);
            //質因數分解
            for (int j = 0; j < primes.size(); ++j)
            {
                while (x % primes[j] == 0)
                {
                    maxP = max(maxP, j);
                    x /= primes[j];
                    A[j][i] ^= 1;
                }
            }
        }
        int freeVar = gaussian_elimination(maxP + 1, n);
        //2**freeVar
        //-1是扣掉都不選的case
        printf("%lld\n", (1LL << freeVar) - 1);
    }
    return 0;
}