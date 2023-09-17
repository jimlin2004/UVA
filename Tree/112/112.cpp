#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool flag; //最後答案

char getNextChar()
{
    char c;
    while (1)
    {
        scanf("%c", &c);
        if (c != ' ' && c != '\n')
            break;
    }
    return c;
}

int getInt(char first_char)
{
    int num = 0;
    bool sign = false; //負號
    char c;
    if (first_char == '-')
    {
        sign = true;
    }
    else
    {
        num = first_char - '0';
    }
    while (1)
    {
        c = getNextChar();
        if (c == '(')
            break;
        num = num * 10 + (c - '0');
    }
    return (sign) ? (-1 * num) : (num);
}

bool parseTree(int path_sum)
{
    int val;
    char c;
    bool left = false, right = false;
    c = getNextChar();
    if (c == ')')
        return true; // empty node
    val = getInt(c); //get node value、亦吃掉left的 '('
    left = parseTree(path_sum - val); //去left
    getNextChar(); //吃掉right的 (
    right = parseTree(path_sum - val); //去right
    
    if ((left && right) && (path_sum - val == 0))
    {
        flag = true;
    }
    getNextChar(); //吃掉 ')'
    return false;
}

int main()
{
    int sum;
    
    while (scanf("%d", &sum) != EOF)
    {
        flag = false;
        getNextChar(); // 取第一個 '('
        parseTree(sum);
        printf("%s\n", (flag) ? "yes" : "no");
    }
    return 0;
}