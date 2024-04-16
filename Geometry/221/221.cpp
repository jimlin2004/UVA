#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define maxn 105

/*
    注: Udebug的測資此程式會差幾筆，但UVA過了

    因為測資maxn才100，所以可以直接用枚舉的
    將building以x, y做排序(因為題目的輸出有要求)
    再將每一個building的xmin、xmax記起來丟掉viewPos裡
    viewPos經過sort與unique後所存的就是要去檢驗的觀察點
    利用這些觀察點去一個個枚舉第i個建築能不能被看到
    building i 被 building k擋住有以下條件:
        1. building i、k包含pos(也就是pos的x座標包含於building i、k的xmin、xmax)
        2. building i的深度比k深
        (以左下角的y判斷，至於原本考慮i的y + depth <= k的y在UVA能過，但在學校與老師輸出不一樣，所以先改成i的y < k的y)
        3. building i的height <= building k的height
    而i被誰擋住也是直接枚舉全部建築即可
*/

struct Building
{
    double x, y;
    double width, depth, height;
    int id;

    bool operator < (const Building& other) const
    {
        if (this->x == other.x)
        {
            return this->y < other.y;
        }
        return this->x < other.x;
    }
};

Building buildings[maxn];
//所有Building的xmin, xmax
vector<double> viewPos;
int n;

inline bool isCover(int index, double pos)
{
    return (buildings[index].x <= pos && pos <= buildings[index].x + buildings[index].width);
}

/*
    直接枚舉building target在pos看過去時會不會被building i遮住
*/
bool isVisible(int target, double pos)
{
    for (int i = 0; i < n; ++i)
    {
        if (target == i)
            continue;
        //注: 寫buildings[i].y + buildings[i].depath <= buildings[target].y UVA也能過，但與學校老師的輸出不同，所以改掉
        if (isCover(i, pos) && (buildings[i].y < buildings[target].y) && (buildings[i].height >= buildings[target].height))
            return false;
    }
    return true;
}

int main()
{
    int Case = 0;
    bool first = true;
    while (scanf("%d", &n) && n)
    {
        viewPos.clear();
        for (int i = 0; i < n; ++i)
        {
            scanf("%lf %lf %lf %lf %lf", &buildings[i].x, &buildings[i].y, &buildings[i].width, &buildings[i].depth, &buildings[i].height);
            buildings[i].id = i + 1;
            viewPos.emplace_back(buildings[i].x);
            viewPos.emplace_back(buildings[i].x + buildings[i].width);
        }

        sort(buildings, buildings + n);
        sort(viewPos.begin(), viewPos.end());
        int viewPosSize = unique(viewPos.begin(), viewPos.end()) - viewPos.begin();

        if (first)
            first = false;
        else
            puts("");

        printf("For map #%d, the visible buildings are numbered as follows:\n", ++Case);
        //經過sort後，buildings[0]一定是最左下的Building，一定看得到
        //方便輸出控制空白才寫的:>
        printf("%d", buildings[0].id);
        //枚舉所有的Building
        for (int i = 1; i < n; ++i)
        {
            //枚舉building[i]在兩viewPos中點(viewPos[i] + viewPos[i + 1])是否看得見
            double midX;
            for (int j = 0; j < viewPosSize - 1; ++j)
            {
                midX = (viewPos[j] + viewPos[j + 1]) / 2;
                if (isCover(i, midX) && isVisible(i, midX))
                {
                    printf(" %d", buildings[i].id);
                    break;
                }
            }
        }
        puts("");
    }
    return 0;
}