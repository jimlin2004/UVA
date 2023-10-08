#include <iostream>
using namespace std;

long long p(int B, int P, int M)
{
    if (P == 0)
        return 1 % M;
    if (P == 1)
        return B;
    long long res = p(B, P >> 1, M) % M;
    res = (res % M) * (res % M);
    res %= M;
    if (P & 1)
    {
        res *= B % M;
        res %= M;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int B, P, M;
    while(cin >> B >> P >> M)
    {
        cout << p(B % M, P, M) << '\n';
    }
}