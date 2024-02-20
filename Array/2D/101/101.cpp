#include <string>
#include <iostream>
using namespace std;

/*
苦工題
基本上就Array 2D照著題目操作
操作分解成
    1. 需要時將a以上(不包含)搬回去
    2. 需要時將b以上(不包含)搬回去
    3. 將a以上(包含，可能只有a或一堆)搬到b那一堆上面
*/

int blocks[30][30];
//[i][0] for i_x, [i][1] for i_y
int position[30][2];
//每個column有多高
int topOfEach[30];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        blocks[i][0] = i;
        position[i][0] = i;
        position[i][1] = 0;
        topOfEach[i] = 1;
    }
    string cmd1;
    string cmd2;
    int a, b;
    int ax, ay, bx, by;
    while (cin >> cmd1 && cmd1 != "quit")
    {
        cin >> a >> cmd2 >> b;
        
        ax = position[a][0];
        ay = position[a][1];
        bx = position[b][0];
        by = position[b][1];
        
        if (ax == bx)
            continue;

        if (cmd1 == "move")
        {
            //將a上面那堆方塊放回去
            int top = topOfEach[ax] - 1;
            while (top != ay)
            {
                int targetNumber = blocks[ax][top];
                int newX = position[targetNumber][0] = targetNumber;
                int newY = position[targetNumber][1] = topOfEach[targetNumber];
                ++topOfEach[newX];
                blocks[newX][newY] = targetNumber;
                blocks[ax][top] = -1;
                --top;
            }
            topOfEach[ax] = ay + 1;
        }

        if (cmd2 == "onto")
        {
            //將b上面那堆方塊放回去
            int top = topOfEach[bx] - 1;
            while (top != by)
            {
                int targetNumber = blocks[bx][top];
                int newX = position[targetNumber][0] = targetNumber;
                int newY = position[targetNumber][1] = topOfEach[targetNumber];
                ++topOfEach[newX];
                blocks[newX][newY] = targetNumber;
                blocks[bx][top] = -1;
                --top;
            }
            topOfEach[bx] = by + 1;
        }

        //將a上面包含a(可能一堆，可能沒東西)放到b上
        for (int y = ay; y < topOfEach[ax]; ++y)
        {
            int newX = position[blocks[ax][y]][0] = bx;
            int newY = position[blocks[ax][y]][1] = topOfEach[bx];
            ++topOfEach[bx];
            blocks[newX][newY] = blocks[ax][y];
            blocks[ax][y] = -1;
        }
        topOfEach[ax] = ay;
    }

    for (int i = 0; i < n; ++i)
    {
        printf("%d:", i);
        for (int j = 0; j < topOfEach[i]; ++j)
        {
            printf(" %d", blocks[i][j]);
        }
        puts("");
    }

    return 0;
}