#include <stdio.h>

int main()
{
    int D, I;
    int N;
    int pos;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &D, &I);
        pos = 1;
        D--;
        while (D--)
        {
            if (I & 1)
            {
                pos = pos << 1;
                I = (I + 1) >> 1;
            }
            else
            {
                pos = (pos << 1) + 1;
                I = I >> 1;
            }
        }
        printf("%d\n", pos);
    }
    return 0;
}