#include <cstdio>
#include <vector>
using namespace std;

/*
數論題
n mod (-2) 可能為-1、0、1，但-1不合法
目的是將-1變成1(結論遇到-1則商+1)
ex: 1024 10進制轉2進制
第0次: 1024 / 2 = 512, 1024 % 2 = 0，試試看512 + 1 = 513，逆推回去是1026，
       也就是多2^1
第1次: 512 / 2 = 256, 512 % 2 = 0，試試看256 + 1 = 257，逆推回去是1028，
       也就是多2^2
結論: 在第i次+1，相當於原來的數字增加2^(i+1)
回到這題
n = b_0 + b_1(-2) + b_2(-2)^2 + b_3(-2)^3 + ...
當n是正數時，第i次mod = -1，則i一定是奇數(因為mod正負只與n的正負有關)
對應到n的表達式是-1*(-2)^i = 2^i，我們把-1變成1，則變成1*(-2)*i = -2^i
因此變1後推回去相當於減少2*2^i = 2^(i + 1)，
這邊減少的我們要補回來，應用上面推導的(商+1)，
在第i次算完後商+1，相當於逆推回去時加上2^(i + 1)
一路算下去，逆推回去得到的n是一樣的

同理可證n是負數的情況
*/

vector<int> res;

int main()
{
    int T;
    int n;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf("%d", &n);
        int mod;
        res.clear();
        while (n)
        {
            mod = n % (-2);
            n /= (-2);
            if (mod == -1)
            {
                mod = 1;
                ++n;
            }
            res.push_back(mod);
        }
        printf("Case #%d: ", t);
        for (int i = res.size() - 1; i >= 0; --i)
        {
            printf("%d", res[i]);
        }
        if (res.size() == 0)
            printf("0");
        puts("");
    }
    return 0;
}