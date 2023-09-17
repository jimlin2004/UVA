#include <iostream>
using namespace std;

struct BigNum
{
    int data[1000]; //4個一位
    int size;
};

BigNum bigNums[1005];

int main()
{
    bigNums[0] = {{1}, 1};
    bigNums[1] = {{1}, 1};
    int carry = 0;
    for (int i = 2; i <= 1000; ++i)
    {
        for (int j = 0; j < bigNums[i - 1].size; ++j)
        {
            bigNums[i].data[j] = bigNums[i - 1].data[j] * i;
            bigNums[i].data[j] += carry;
            carry = bigNums[i].data[j] / 10000;
            bigNums[i].data[j] %= 10000;
        }
        bigNums[i].size = bigNums[i - 1].size;
        if (carry != 0)
        {
            bigNums[i].data[bigNums[i].size++] = carry;
            carry = 0;
        }
    }
    int num;
    while (scanf("%d", &num) != EOF)
    {
        printf("%d!\n", num);
        printf("%d", bigNums[num].data[bigNums[num].size - 1]);
        for (int i = bigNums[num].size - 2; i >= 0; --i)
        {
            printf("%0.4d", bigNums[num].data[i]);
        }
        puts("");
    }
    return 0;
}