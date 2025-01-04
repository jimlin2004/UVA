#include <cstdio>
#include <cmath>

/*
    思考結論題
    永遠可以找到中間的數字
    並且拿中間的數字去減後面的每個數字
    如
    1 2 3 4 5 6 7 8 9
    可以用中間的5去減掉後面
    變 1 2 3 4 5 1 2 3 4
    所以可以折過來當作
    1 2 3 4 5解
    這樣的思維下去就可以找到公式
    對於1 2 3 ... n
    最少需要下高斯[log2(n)] + 1次可以消到全部都是0
*/

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
        printf("%d\n", (int)log2(n) + 1);
    return 0;
}