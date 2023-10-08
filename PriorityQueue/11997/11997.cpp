#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct Item
{
    int sum, index;
    bool operator < (const Item& other) const
    {
        return this->sum > other.sum;
    }
};

void merge(int A[], int B[], int C[], int k)
{
    priority_queue<Item> pq;

    //sort過的B[0]是B中最小的，將其加上A的所有元素
    for (int i = 0; i < k; ++i)
        pq.push({A[i] + B[0], 0});
    
    for (int i = 0; i < k; ++i)
    {
        Item item = pq.top();
        pq.pop();
        C[i] = item.sum;

        if (item.index + 1 < k)
            pq.push({item.sum - B[item.index] + B[item.index + 1], item.index + 1});
    }
}

int main()
{
    int k;
    int A[755];
    int B[755];
    while (scanf("%d", &k) != EOF)
    {
        for (int i = 0; i < k; ++i)
            scanf("%d", &A[i]);
        sort(A, A + k);
        
        for(int i = 1; i < k; ++i)
        {
            for (int j = 0; j < k; ++j)
                scanf("%d", &B[j]);
            sort(B, B + k);

            merge(A, B, A, k);
        } 

        printf("%d", A[0]);
        for (int i = 1; i < k; ++i)
            printf(" %d", A[i]);
        puts("");
    }
    return 0;
}