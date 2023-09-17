#include <stdio.h>
#include <stdbool.h>

int main()
{
    char c;
    bool isFirst = true;
    while ((c = getchar()) != EOF)
    {
        if (c == '"')
        {
            if (isFirst)
            {
                putchar('`');
                putchar('`');
            }
            else
            {
                putchar('\'');
                putchar('\'');
            }
            isFirst = !isFirst;
        }
        else
            putchar(c);
    }
    return 0;
}