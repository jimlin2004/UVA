#include <iostream>
#include <cstring>
#include <string>
using namespace std;

char keyboard[] = " `1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./" ;
char table[256];

int main()
{
    for (int i = 0; i < 256; ++i)
    {
        table[i] = i;
    }
    for (int i = 2; i < strlen(keyboard); ++i)
    {
        table[keyboard[i]] = keyboard[i - 1];
    }
    string input;
    while (getline(cin, input))
    {
        for (int i = 0; i < input.size(); ++i)
        {
            printf("%c", table[input[i]]);
        }
        puts("");
    }
    return 0;
}