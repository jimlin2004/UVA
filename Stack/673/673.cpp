#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

void clearStack(stack<char>& sk)
{
    while (!sk.empty())
        sk.pop();
}

int main()
{
    stack<char> sk;
    int n;
    char input[1000];
    bool flag;
    scanf("%d", &n);
    getchar(); // '\n'
    while (n--)
    {
        clearStack(sk);
        fgets(input, 1000, stdin);
        flag = false;
        for (int i = 0; i < strlen(input) - 1; ++i)
        {
            switch (input[i])
            {
            case '(':
                sk.push('(');
                break;
            case '[':
                sk.push('[');
                break;
            case ')':
                if (sk.empty())
                    flag = true;
                else if (sk.top() != '(')
                    flag = true;
                else
                    sk.pop();
                break;
            case ']':
                if (sk.empty())
                    flag = true;
                else if (sk.top() != '[')
                    flag = true;
                else
                    sk.pop();
                break;
            default:
                break;
            }
            if (flag)
                break;
        }
        if (flag || (!sk.empty()))
            puts("No");
        else
            puts("Yes");
    }
}