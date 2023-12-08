#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

/*
核心概念:
    暴力一點
    直接枚舉nums(16個數)任意挑4個出來，有C(16, 4)種組合
    組合用array或其他的不好表示，用bit set(在此用int bit)做狀態壓縮ex: 0001001100000001代表位置為1、9、10、13的x
    這4個x的組合的排列(4!種)依序直接套入題目公式 4*x_0 + 3*x_1 + 2*x_2 + x_3 = t
    然後紀錄每個t有幾個解(枚舉t時就有了)
    再紀錄t的同時要檢查之前一樣算出t的解中與現在的解有沒有交集，
    有交集就不能與目前的解作為平衡等式的左右邊(每個數同時只能用一次)
    交集用&
    如果沒有交集它們就可以作為一組平衡等式的左右邊(設為prevS, currS)
    記為solutionCount[prevS | currS]++，其中 | 是聯集
    如此solutionCount[i]是 prevS | currS = i => prevS 與 currS作為平衡等式的左右邊組合的數量統計
    最後統計result
    遍歷soultionCount
    N = 2 ^ 16 - 1
    公式是 1/2[sum{form 0 to 2 ^ 16 - 1}{solutionCount[i] * solutionCount[i ^ (N - 1)]}]
        當solutionCount[i] != 0時，
        solutionCount[i]是一組(或多組)用16個x挑8個的平衡等式組合(不失一般性，假設為水平的等式)，
        i是16個挑8個
        solutionCount[i ^ (N - 1)]是另一組(或多組)用另外8個x平衡等式組合(由上面的假設，此8個x是垂直的等式)
        i ^ (N - 1) 是i的bit set補集(以此達到挑出其他8個的方法)
        最後乘起來相加即為答案
        而若另外的8個x並不能湊成一組平衡等式，此時solutionCount[i ^ (N - 1)]會 = 0
        乘起來亦是0不影響答案
        最後1/2是為了消去遍歷造成的重複計算
*/

//輸入的資料
int nums[16];

//最多會需要1024 * 4 + 1023 * 3 + 1022 * 2 + 1021 * 1
//直接開1024 * 10 + 5
const int M = 10245;
//2^16
const int N = (1 << 16);

//套題目公式算出來的4個x位置(用整數bits來狀態壓縮)
vector<int> solution[M];
//每一個可平衡的等式數量
int solutionCount[N];
//存任挑4個數
//開16格是因為狀態壓縮的bits是16bit，避免出現bits有16個1會出錯的情況
int x[16]; 

void init()
{
    sort(nums, nums + 16);
    for (int i = 0; i < M; ++i)
        solution[i].clear();
    memset(solutionCount, 0, sizeof(solutionCount));
}

//檢查n的bit 1 是不是4個(也就是4個不同位置的x)
bool check(int n)
{
    int count = 0;
    int bitmask = 1;
    for (int i = 0; i < 16; ++i)
    {
        if (n & bitmask)
            x[count++] = nums[i];
        bitmask <<= 1;
    }
    return count == 4;
}

long long solve()
{
    long long res = 0;
    int t;
    //直接枚舉0 ~ (2^16 - 1)中(設為i)
    //且i有4個bit 1的
    //相當於從nums(16個)挑出4個套公式算算看
    for (int i = 0; i < N; ++i)
    {
        //bits中有4個1
        if (check(i))
        {
            //此時x[0], x[1], x[2], x[3]是由小排到大的
            //枚舉這4個數的排列組合(4!種)
            do
            {
                //套題目公式算出值
                t = x[0] * 4 + x[1] * 3 + x[2] * 2 + x[3];
                //檢查所有之前算出來也是t的組合
                //與當前的組合不能有重複的bit(因為題目說數字只能同時挑一次)
                //用 & 算交集，交集 == 0相當於沒有重複
                for (int k = 0; k < solution[t].size(); ++k)
                {
                    if ((solution[t][k] & i) == 0)
                    {
                        //用 | 算出聯集，合併成一組答案
                        ++solutionCount[solution[t][k] | i];
                    }
                }
                solution[t].emplace_back(i);
            } while (next_permutation(x, x + 4));
        }
    }

    //統計答案
    //用 ^ 算出補集
    //相當於假設solutionCount[i]是題目中水平的等式
    //其中i是水平等式的左邊與右邊bit set聯集(也就是用到的8個數的位置用16bits來代表)
    //那solutionCount[i ^ (N - 1)]就是剩下的8個x用於垂直的等式的解個數
    //不用擔心只有水平等式有解的情況，因為此時solutionCount[i ^ (N - 1)] = 0
    //最後乘起來也是0
    for (int i = 0; i < N; ++i)
    {
        res += solutionCount[i] * solutionCount[i ^ (N - 1)];
    }
    //去掉重複計算的
    return res / 2;
}

int main()
{
    int Case = 0;
    while (scanf("%d", &nums[0]) && nums[0])
    {
        for (int i = 1; i < 16; ++i)
        {
            scanf("%d", &nums[i]);
        }
        init();
        printf("Case %d: %lld\n", ++Case, solve());
    }
    return 0;
}