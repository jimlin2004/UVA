#include <iostream>
#include <cstring>
#include <unordered_map>
#include <string>
using namespace std;

//把board的chesses的座標變成串起來的字串去hash map比對

string boardToString(int board[55][55], int n)
{
    string str = "";
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (board[i][j] == 1)
            {
                str += to_string(i) + to_string(j);
            }
        }
    }
    return str;
}

void rotateBoard(int rotatedBoard[55][55], int board[55][55], int n)
{
    //觀察出旋轉公式
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            rotatedBoard[n - i + 1][j] = board[j][i];
        }
    }
}

void copy(int dst[55][55], int src[55][55], int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            dst[i][j] = src[i][j];
        }
    }
}

void printBoard(int board[55][55], int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}

unordered_map<string, bool> mp;

int main()
{
    int board[55][55];
    int rotatedBoard[55][55];
    int n;
    int x, y;
    char cmd;
    while (cin >> n && n)
    {
        memset(board, 0, sizeof(board));
        mp.clear();
        int player = 1;
        bool draw = true;
        for (int i = 1; i <= 2 * n; ++i)
        {
            cin >> x >> y >> cmd;
            if (!draw)
                continue;
            
            if (cmd == '+')
                board[y][x] = 1;
            else
                board[y][x] = 0;
            
            string boardStr = boardToString(board, n);

            for (int j = 0; j < 4; ++j)
            {
                rotateBoard(rotatedBoard, board, n);
                
                if (mp.find(boardToString(rotatedBoard, n)) != mp.end())
                {
                    cout << "Player " << ((player == 1) ? 2 : 1) << " wins on move " << i << '\n';
                    draw = false;
                    break;
                }

                copy(board, rotatedBoard, n);
            }

            mp.insert({boardStr, true});
            player = (player == 2) ? 1 : 2;
        }
        if (draw)
            cout << "Draw\n";
    }
    return 0;
}