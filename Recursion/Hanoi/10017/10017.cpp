#include <cstdio>
#include <cstring>
using namespace std;

//以下是複習一下最簡單的Hanoi程式
/*
    1. 利用C作為暫存將N - 1個盤子從A移至B
    2. 將A剩下最大的那個盤子從A移動到C
    3. 利用A將剩下的n - 1個盤子從B移動到C
*/
//這裡可以將A想成起始柱，B為中轉柱，C為目標柱

// void move(int n, char from, char to)
// {
//     printf("Move %d from %c to %c\n", n, from, to);
// }

// void hanoi(char A, char B, char C, int n)
// {
//     if (n == 1)
//     {
//         //只剩一個盤子，就將該盤子直接從A搬到C
//         move(n, A, C);
//         return;
//     }
//     //盤子大於1個，就需要先將n - 1個盤子從起始柱A透過目標柱C搬到中轉柱B
//     hanoi(A, C, B, n - 1);
//     //在起始柱A的盤子可以直接搬到目標柱C
//     move(n, A, C);
//     //將中轉柱B的盤子透過A移動到目標柱C
//     hanoi(B, A, C, n - 1);
// }

// int main()
// {
//     hanoi('A', 'B', 'C', 3);
//     return 0;
// }

//正文

//這題就是考Hanoi

#define A_PEG 1
#define B_PEG 2
#define C_PEG 3
#define MAX_DISKS 255
#define MAX_PEGS 5

bool pegs[MAX_PEGS][MAX_DISKS];
int n_disks, n_maxSteps;

int steps = 0;
bool stepsReached = false;

//印出A、B、C的狀態
void printHanoi()
{
    if (steps > n_maxSteps)
    {
        stepsReached = true;
        return;
    }
    puts("");
    for (int i = A_PEG; i <= C_PEG; ++i)
    {
        printf("%c=>", (char)('A' + i - 1));

        //每一根柱子的最一開始要輸出3個空格(這裡拆成多輸出的2格 + 原本預設會輸出的一格)
        bool isNeedOutputSpace = true;
        for (int j = n_disks; j >= 1; --j)
        {
            if (pegs[i][j])
            {
                if (isNeedOutputSpace)
                {
                    printf("  ");
                    isNeedOutputSpace = false;
                }
                printf(" %d", j);
            }
        }
        puts("");
    }

    ++steps;
}

void move(int n, int from, int to)
{
    pegs[from][n] = false;
	pegs[to][n] = true;
	printHanoi();
}

void hanoi(int n, int A, int B, int C)
{
    if (stepsReached)
        return;
    if (n == 1)
    {
        move(n, A, C);
        return;
    }
    hanoi(n - 1, A, C, B);
    move(n, A, C);
    hanoi(n - 1, B, A, C);
}

int main()
{
    int Case = 0;
    bool first = true;                                 //注意下面是or不是and，因為可以一個是0
    while (scanf("%d %d", &n_disks, &n_maxSteps) != EOF && (n_disks != 0 || n_maxSteps != 0))
    {
        //老師的最後一行沒換行，但UVA有
        // if (first)
        //     first = false;
        // else
            // puts("");
        printf("Problem #%d\n", ++Case);

        steps = 0;
        stepsReached = false;
        memset(pegs, 0, sizeof(pegs));
        //將disks放到A柱
        for (int i = 1; i <= n_disks; ++i)
            pegs[A_PEG][i] = true;
        //先輸出一次初始狀態
        printHanoi();
        hanoi(n_disks, A_PEG, B_PEG, C_PEG);
        puts("");
    }
    return 0;
}