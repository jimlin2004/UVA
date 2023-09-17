#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int k, num, numOfDigit, ans, temp, sum;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d", &num);
        numOfDigit = (int)log10(num);
        //一個數的 generator 最少只會到 9∗位數這麼多
        for (int j = num; j > num - 10 * numOfDigit; j--)
        {
            temp = j;
            sum = 0;
        }
    }
    return 0;
}