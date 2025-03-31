#include <bits/stdc++.h>
using namespace std;

// 考矩陣快速冪而已
// A的填法就是第一row是題目給的係數
// 之後的row是
// 1 0 0 0 0 ...
// 0 1 0 0 0 ...
// 0 0 1 0 0 ...
// 0 0 0 1 0 ...
// 0 0 0 0 1 ...
// 以此類推

long long mod;

struct Matrix
{
    int m, n;
    vector<vector<long long>> vals;
    Matrix(int m, int n)
        : m(m), n(n), vals(m, vector<long long>(n, 0))
    {
    }

    Matrix operator * (const Matrix& other) const
    {
        Matrix res(m, other.n);

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < other.n; ++j)
            {
                for (int k = 0; k < n; ++k)
                {
                    res.vals[i][j] = (res.vals[i][j] + ((vals[i][k] % mod) * (other.vals[k][j] % mod)) % mod) % mod;
                }
            }
        }

        return res;
    }
};


Matrix qpow(Matrix A, int n)
{
    Matrix res(A.m, A.n);
    // 初始化成單位矩陣
    for (int i = 0; i < res.m; ++i)
        res.vals[i][i] = 1;
    
    while (n)
    {
        if (n & 1)
            res = res * A;
        A = A * A;
        n >>= 1;
    }

    return res;
}


int main()
{
    long long d, n;

    vector<long long> coeffs;
    vector<long long> initVals;

    while (scanf("%lld %lld %lld", &d, &n, &mod))
    {
        if (d == 0 && n == 0 && mod == 0)
            break;

        coeffs.clear();
        initVals.clear();

        Matrix A(d, d);
        Matrix b(d, 1);

        long long val;
        for (int i = 0; i < d; ++i)
        {
            scanf("%lld", &val);
            coeffs.emplace_back(val % mod);
        }

        for (int i = 0; i < d; ++i)
        {
            scanf("%lld", &val);
            initVals.emplace_back(val % mod);
        }

        // 填 A
        for (int i = 0; i < d; ++i)
            A.vals[0][i] = coeffs[i];
        for (int i = 1, j = 0; i < d; ++i, ++j)
            A.vals[i][j] = 1;

        // 填b
        for (int i = 0; i < d; ++i)
            b.vals[d - i - 1][0] = initVals[i];
        
        // 特判
        if (n <= d)
        {
            printf("%lld\n", b.vals[n - 1][0] % mod);
            continue;
        }

        Matrix res = qpow(A, n - d) * b;
        printf("%lld\n", res.vals[0][0]);
    }
    return 0;
}