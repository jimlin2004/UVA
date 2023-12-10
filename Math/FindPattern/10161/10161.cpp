#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

/*
找規律
對角線是1、3、7、13...
相差2、4、6...
然後用奇數偶數行用減法算出答案
*/

vector<int> diagonal;

void getDiagonal()
{
    diagonal.emplace_back(1);
    int diff = 2;
    while (diagonal.back() <= 2000000005)
    {
        diagonal.emplace_back(diagonal.back() + diff);
        diff += 2;
    }
}

int main()
{
    getDiagonal();

    int n;

    while (scanf("%d", &n) && n)
    {
        //大於等於中最小的
        auto it = lower_bound(diagonal.begin(), diagonal.end(), n);
        int diagonalIndex = (it - diagonal.begin());
        if ((*it) == n)
        {
            printf("%d %d\n", diagonalIndex + 1, diagonalIndex + 1);
            continue;
        }

        //修正lower_bound抓到更大的一個的case
        if (n < diagonal[diagonalIndex] - (diagonalIndex))
        {
            --diagonalIndex;
        }

        if (diagonalIndex % 2 == 0)
        {
            if (diagonal[diagonalIndex] > n)
            {
                printf("%d %d\n", diagonalIndex + 1, diagonalIndex + 1 - ( diagonal[diagonalIndex]- n));
            }
            else
            {
                printf("%d %d\n", diagonalIndex + 1 - (n - diagonal[diagonalIndex]), diagonalIndex + 1);
            }
        }
        else
        {
            if (diagonal[diagonalIndex] > n)
            {
                printf("%d %d\n", diagonalIndex + 1 - (diagonal[diagonalIndex]- n), diagonalIndex + 1);
            }
            else
            {
                printf("%d %d\n", diagonalIndex + 1, diagonalIndex + 1 - (n - diagonal[diagonalIndex]));
            }
        }
    }

    return 0;
}