#include <bits/stdc++.h>
using namespace std;

// 用矩陣快速冪去算費氏數列

long long mod = 0;

struct Matrix
{
    vector<vector<long long>> vals;
    int m;
    int n;

    Matrix(int m, int n) 
    {
        this->m = m;
        this->n = n;
        vals.assign(m, vector<long long>(n, 0));
    }

    Matrix operator * (const Matrix& other) const
    {
        // 新的是 (a * b) * (b * c) -> (a * c)
        Matrix res(this->m, other.n);
        
        for (int i = 0; i < this->m; ++i)
        {
            for (int j = 0; j < other.n; ++j)
            {
                for (int k = 0; k < this->n; ++k)
                {
                    res.vals[i][j] += (this->vals[i][k] * other.vals[k][j]) % mod;
                    res.vals[i][j] %= mod;
                }
            }
        }

        return res;
    }
};


Matrix qpow(Matrix mat, long long n)
{
    Matrix res(mat.m, mat.n);
    // 初始化成單位矩陣
    for (int i = 0; i < res.m; ++i)
        res.vals[i][i] = 1;
    
    while (n)
    {
        if (n & 1)
            res = res * mat;
        mat = mat * mat;
        n >>= 1;
    }

    return res;
}


int main()
{
    long long n, m;

    // 費氏數列基礎項
    Matrix base(2, 1);
    base.vals = {{1}, {0}};
    // 費氏數列轉移項
    Matrix A(2, 2);
    A.vals = {{1, 1}, {1, 0}};

    while (scanf("%lld %lld", &n, &m) != EOF)
    {
        // 特判
        if (n == 0)
        {
            puts("0");
            continue;
        }

        mod = (1 << m);

        Matrix res = qpow(A, n - 1) * base;

        printf("%lld\n", res.vals[0][0]);
    }

    return 0;
}