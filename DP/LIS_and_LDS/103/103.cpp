#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

/*
經典題
兩種做法:
    一. 將partial order關係轉為DAG，問題變成找DAG最長路徑(Floyd-Warshall)
    二. 利用Greedy與sort，將Box的每個邊長做sort(小到大)，將Boxes做排序(字典序，Greedy)
        最後就只剩下用LIS找出最大的Box序列，再打印LIS即可
    <注>因為此題只有partial order的大小關係，LIS用O(nlongn)不好做，我們不知道LIS尾巴留誰最好
        所以要用O(n^2)的方式
*/

struct Box
{
    int number;
    vector<int> dimensions;
    //字典序
    bool operator < (const Box& other) const
    {
        for (int i = 0; i < this->dimensions.size(); ++i)
        {
            if (this->dimensions[i] > other.dimensions[i])
                return false;
            if (this->dimensions[i] < other.dimensions[i])
                return true;
        }
        return true;
    }
    bool canContain (const Box& other) const
    {
        for (int i = 0; i < this->dimensions.size(); ++i)
        {
            if (this->dimensions[i] <= other.dimensions[i])
                return false;
        }
        return true;
    }
};

Box boxes[35];

// struct Item
// {
//     int boxIndex;
//     bool operator < (const Item& other) const
//     {
//         return boxes[this->boxIndex] < boxes[other.boxIndex];
//     }
// };

int LIS[35];
int path[35];

void printLIS(int index)
{
    if (index == -1)
        return;
    printLIS(path[index]);
    printf("%d ", boxes[index].number);
}

int main()
{
    int boxN, boxDim;
    while (scanf("%d %d", &boxN, &boxDim) != EOF)
    {
        int dim;
        for (int i = 0; i < boxN; ++i)
        {
            boxes[i].number = i + 1;
            boxes[i].dimensions.clear();
            for (int d = 0; d < boxDim; ++d)
            {
                scanf("%d", &dim);
                boxes[i].dimensions.emplace_back(dim);
            }
            sort(boxes[i].dimensions.begin(), boxes[i].dimensions.end());
        }

        sort(boxes, boxes + boxN);

        //這題用O(nlogn不好解，我們不確定尾巴留誰好)
        // LIS.push_back({0});
        // for (int i = 1; i < boxN; ++i)
        // {
        //     Item item = {i};
        //     if (LIS.back() < item)
        //         LIS.emplace_back(item);
        //     else
        //         *lower_bound(LIS.begin(), LIS.end(), item) = item;
        // }
        //改用O(n^2)
        for (int i = 0; i < boxN; ++i)
            LIS[i] = 1;
        memset(path, -1, sizeof(path));
        for (int i = 0; i < boxN; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (boxes[i].canContain(boxes[j]))
                {
                    if (LIS[i] < LIS[j] + 1)
                    {
                        LIS[i] = LIS[j] + 1;
                        path[i] = j;
                    }
                }
            }
        }

        int maxLen = -1;
        int LISTail = -1;
        for (int i = 0; i < boxN; ++i)
        {
            if (maxLen < LIS[i])
            {
                maxLen = LIS[i];
                LISTail = i;
            }
        }

        printf("%d\n", maxLen);
        printLIS(path[LISTail]);
        printf("%d\n", boxes[LISTail].number);
    }
    return 0;
}