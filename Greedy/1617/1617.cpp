#include <iostream>
#include <algorithm>
using namespace std;

/*
    排程問題
    先將segment做先右再左的sort(小到大)
    維護一個currR作為現在已安排的最右端
    空檔數cnt = 0

    每個工作segment -> [l, r]

    注意: 底下的放在左邊是對的原因
        deadline升續，start也升序，所以一定放得下
        因為我們先將segment先右再左拿，所以如果連續拿到r相同的工作，s1.l 一定 <= s2.l
        此時currR的左邊一定夠
        因為題目不會給非法的input
        不會有segment完全重疊的情況
        詳細可看推導.png

    分狀況討論:
    case 1:
        currR == r 
        代表[l, r]在currR的右邊，
        此時只要將該工作分配在currR的左邊即可
        currR不用更新
    case 2:
        currR < l
        代表整個工作[l, r]在currR的右邊，
        一定有空檔產生，所以currR = r, ++cnt
    case 3:
        l <= currR < R
        此時工作[l, r]跨越currR
        由於上一個工作如果連續的話會在currR的左邊，
        所以此時只要將此工作安排在[currR, currR + 1]的位置
        即可與之前的工作繼續相連
        記得更新currR++

    也就是能放就一直往左邊堆就對了，sort後保證不會超出start時限
*/

#define maxn 300005

struct Segment
{
    int l, r;
    bool operator < (const Segment& other) const
    {
        if (this->r == other.r)
            return this->l < other.l;
        return this->r < other.r;
    }
};

Segment segments[maxn];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &segments[i].l, &segments[i].r);
        }

        sort(segments, segments + n);

        int currR = segments[0].r;
        int res = 0;
        for (int i = 1; i < n; ++i)
        {
            if (segments[i].r == currR)
                continue;
            else if (currR < segments[i].l)
            {
                currR = segments[i].r;
                ++res;
            }
            else
            {
                ++currR;
            }
        }

        printf("%d\n", res);
    }
    return 0;
}
