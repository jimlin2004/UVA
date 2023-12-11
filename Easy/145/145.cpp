#include <cstdio>
using namespace std;

double charge[5][3] = {
    {0.10, 0.06, 0.02}, {0.25, 0.15, 0.05},
    {0.53, 0.33, 0.13}, {0.87, 0.47, 0.17},
    {1.44, 0.80, 0.30}
};

int main()
{
    char phone[10];
    char step;
    int fromH, fromM;
    int toH, toM;
    int time1, time2, time3;
    while (scanf("%c", &step) && (step != '#'))
    {
        scanf("%8s %d %d %d %d", phone, &fromH, &fromM, &toH, &toM);
    
        double total = 0.0;
        int stepIndex = step - 'A';
        time1 = time2 = time3 = 0;

        if (fromH != toH || (fromH == toH && fromM > toM) || (fromH == toH && fromM == toM))
        {
            if (8 <= fromH && fromH < 18)
            {
                time1 += 60 - fromM;
                ++fromH;
                total += charge[stepIndex][0] * (60 - fromM);
                fromM = 0;
            }
            else if (18 <= fromH && fromH < 22)
            {
                time2 += 60 - fromM;
                ++fromH;
                total += charge[stepIndex][1] * (60 - fromM);
                fromM = 0;
            }
            else if (22 <= fromH || fromH < 8)
            {
                time3 += 60 - fromM;
                ++fromH;
                total += charge[stepIndex][2] * (60 - fromM);
                fromM = 0;
            }

            fromH %= 24;
        }
        else if (fromH == toH && fromM < toM)
        {
            if (8 <= fromH && fromH < 18)
            {
                time1 += toM - fromM;
                total += charge[stepIndex][0] * (toM - fromM);
            }
            else if (18 <= fromH && fromH < 22)
            {
                time2 += toM - fromM;
                total += charge[stepIndex][1] * (toM - fromM);
            }
            else if (22 <= fromH || fromH < 8)
            {
                time3 += toM - fromM;
                total += charge[stepIndex][2] * (toM - fromM);
            }

            printf("%10s%6d%6d%6d%3c%8.2lf\n", phone, time1, time2, time3, step, total);
            getchar(); // for \n

            continue;
        }

        while (fromH != toH)
        {
            if (8 <= fromH && fromH < 18)
            {
                time1 += 60;
                ++fromH;
                total += charge[stepIndex][0] * 60;
            }
            else if (18 <= fromH && fromH < 22)
            {
                time2 += 60;
                ++fromH;
                total += charge[stepIndex][1] * 60;
            }
            else if (22 <= fromH || fromH < 8)
            {
                time3 += 60;
                ++fromH;
                total += charge[stepIndex][2] * 60;
            }

            fromH %= 24;
        }

        if (8 <= toH && toH < 18)
        {
            time1 += toM;
            total += charge[stepIndex][0] * toM;
        }
        else if (18 <= fromH && fromH < 22)
        {
            time2 += toM;
            total += charge[stepIndex][1] * toM;
        }
        else if (22 <= fromH || fromH < 8)
        {
            time3 += toM;
            total += charge[stepIndex][2] * toM;
        }

        printf("%10s%6d%6d%6d%3c%8.2lf\n", phone, time1, time2, time3, step, total);
    
        getchar(); // for \n
    }
    return 0;
}