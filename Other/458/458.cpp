#include <stdio.h>

int main()
{
    int key = 'J' - 'C';
    char c;
    while (scanf("%c", &c) != EOF)
    {
        if (c == '\n')
            printf("\n");
        else
            printf("%c", c - key);
    }
    return 0;
}