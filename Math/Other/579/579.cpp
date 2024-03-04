#include <cstdio>
#include <cmath>
using namespace std;

//題意是要求時針與分針的夾角

int main()
{
    int h, m;
    while (scanf("%d:%d", &h, &m))
    {
        if (h == 0 && m == 0)
            break;

        if (h >= 12)
            h -= 12;
        
        // 360 / 12 = 30  // * 30.0是因為1小時時針動30度
        double angleH = h * 30.0 + (m / 60.0) * 30.0;
        // 360 / 60 = 6
        double angleM = m * 6.0;
        double res = fabs(angleH - angleM);
        if (res >= 180.0)
            res = 360 - res;
        printf("%.3lf\n", res);
    }
    return 0;
}