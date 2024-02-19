#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct Box
{
    int number;
    vector<int> dimensions;
    bool operator < (const Box& other) const
    {
        bool isLess = true;
        for (int i = 0; i < this->dimensions.size(); ++i)
        {
            if (this->dimensions[i] >= other.dimensions[i])
            {
                isLess = false;
                break;
            }
        }
        return isLess;
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
    printf("%d ", index);
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
            for (int j = 0; j < boxN; ++j)
            {
                if (boxes[j] < boxes[i])
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
        printf("%d\n", LISTail);
    }
    return 0;
}