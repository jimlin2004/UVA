#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define maxn 105

/*
    配合推導.png

    很複雜的幾何題

    題意: 找出一個點，使該點到外面的凸多邊形的距離最大，最後回傳距離即可(不用找點)
    題意很清楚就是要找凸多邊形的內心，求內心與邊的距離

    由於坐標系有無限個點，不可能用一個個試的方式
    所以想到二分法對答案二分，搜出mid <- [l, r)，初始l = 0, r = 10000

    但怎麼知道mid太大或可以更大
    方法很複雜(老師解)
    基本想法是考慮將凸多邊形的每個邊往那個邊的垂直方向向內移動mid距離
    然後去看移動之後的每個邊的半平面交集是否還可以形成凸多邊形(形狀可能與原本不一樣)
    如果可以就代表答案可以在更大，否則就是mid太大了
    最後答案在 l

    但在這裡還有幾何問題要實作

    1. 如何移動邊
    sol. 
        要移動邊，首先要先用程式表示直線的方程式
        點斜式、截距式、一般式用程式不好寫，想到參數式會是比較簡單的做法(一點加上方向向量)
        且移動邊時用參數式我們只需要移動參數式那一點的座標即可(所以用參數式)
        再來邊要往那條邊的垂直方向移動mid單位距離，
        很明顯(邊的單位法向量 * mid)即為邊要移動的方向
        由於參數式有直線的方向向量(v)，則該直線的法向量(n) 即為 n = (-v.y, v.x) <- 高中數學(xy交換加負號)
        最後只需將(邊的單位法向量 * mid) + (邊的p)即為移動後的邊的參數式
    2. 如何得到半平面交集
    sol. 
        需要維護一個單調佇列
        半平面交集是一個凸多邊形，所以要維護半平面交集的類似凸包的邊
        這裡半平面交集的邊是narrow[]中挑出來的，
        將narrow[]的邊先以angle去由小到大排序(以保持逆時針選取邊)
        並維護交集陣列，如果單調佇列有2個邊以上就會產生交點
        如果上個交點是在當前的邊的右側，那上一條邊就不會是半平面交集的邊(參考"半平面說明1.png")
        所以當前新的邊會影響單調佇列的尾端邊
        還有一種狀況是快結束時，新的邊會對單調佇列的頭端邊有影響(見"半平面說明2.png")
        這也是為什麼用單調佇列維護頭尾即可找出半平面交集

        實際撰寫程式見下方
    3. 兩參數式求交點
    sol. 有公式(需推導)
    4. 參數式與向量計算還有點都要實作
*/

class Vector;

//二維平面點
class Point
{
public:
    double x, y;

    Point() = default;

    Point(double x, double y) 
        : x(x), y(y)
    {
    }

    Point operator + (const Vector& vec) const;
};

//二維向量
class Vector
{
public:
    double x, y;
    Vector() = default;
    Vector(const Vector& other)
        : x(other.x), y(other.y)
    {
    }
    Vector(double x, double y)
        : x(x), y(y)
    {
    }

    Vector operator * (const double val) const
    {
        return Vector(this->x * val, this->y * val);
    }

    //向量常用的函式

    //向量長度
    inline double getLength() const
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    //內積
    static inline double dot(const Vector& vec1, const Vector& vec2)
    {
        return (vec1.x * vec2.x + vec1.y * vec2.y);
    }

    static inline double getCrossProduct(const Vector& v1, const Vector& v2)
    {
        return (v1.x * v2.y - v1.y * v2.x);
    }

    static inline Vector getDirectionVectorFormPoints(const Point& p1, const Point& p2)
    {
        return Vector(p2.x - p1.x, p2.y - p1.y);
    }

    //得到單位法向量(座標平面上的正轉90度)
    static Vector getNormal(const Vector& vec)
    {
        double length = vec.getLength();
        return Vector(-vec.y / length, vec.x / length);
    }
};

Point Point::operator + (const Vector& vec) const
{
    return Point(this->x + vec.x, this->y + vec.y);
}

//用參數式表示直線方程式
class Line
{
public:
    //一點
    Point p;
    //方向向量
    Vector v;
    //法向量
    Vector normal;
    //與x軸的夾角
    double angle;

    Line() = default;

    Line(const Point& point, const Vector& vec)
        : p(point), v(vec)
    {
        this->angle = atan2(this->v.y, this->v.x);
    }

    bool operator < (const Line& other) const
    {
        return this->angle < other.angle;
    }

    void setDirectionVector(const Vector& newV)
    {
        this->v = newV;
        this->angle = atan2(this->v.y, this->v.x);
    }
};

//原本的凸多邊形的點(逆時針)
Point points[maxn];
//原本的凸多邊形邊的參數式
Line lines[maxn];
//內縮之後的凸多邊形的參數式
Line narrow[maxn];

//點是否在直線的左邊
inline bool onLeft(const Line& line, const Point& point)
{
    return (Vector::getCrossProduct(line.v, Vector::getDirectionVectorFormPoints(line.p, point)) > 0);
}

//求兩參數式直線的交點(公式需推導)
Point getIntersection(const Line& l1, const Line& l2)
{
    Vector u = Vector::getDirectionVectorFormPoints(l2.p, l1.p);
    double t = Vector::getCrossProduct(l2.v, u) / Vector::getCrossProduct(l1.v, l2.v);
    return l1.p + (l1.v * t);
}

//求narrow的半平面相交的多邊形交數
int halfplaneIntersection(int n)
{
    //將narrow以angle去由小到大排列
    sort(narrow, narrow + n);

    //單調佇列
    int first, last;
    Line* q = new Line[n];
    //交點
    Point* intersections = new Point[n];

    q[first = last = 0] = narrow[0];
    for (int i = 1; i < n; ++i)
    {
        //<注意> 要先檢查單調佇列尾端再檢查頭端，否則會使得搜尋時半平面可能變大(找的範圍不對)
        //如果單調佇列中不只一條邊時，first != last，此時要檢查上個交點是否在新的邊的右側
        //if true -> 單調佇列的尾端邊不是半平面交集的邊
        while (first < last && !onLeft(narrow[i], intersections[last - 1]))
            --last;
        //快結束時，新的邊開始對單調佇列頭端邊有影響，所以也要檢查
        while (first < last && !onLeft(narrow[i], intersections[first]))
            ++first;
        
        //將新的邊加入到單調佇列
        q[++last] = narrow[i];
        //如果新的邊與上個邊共線(也就是向量平行且方向相同)
        if (fabs(Vector::getCrossProduct(q[last].v, q[last - 1].v)) < 1e-7)
        {
            //捨棄新的邊
            --last;
            //如果新的邊的點在最後一個邊的左邊，最後一個邊改為新的邊
            //因為我們要求的是每個邊的左側半平面，所以只要保留更靠內的邊即可
            //判斷方法就是如果新的邊的參數式中的點在最後一個邊的左側
            //此時新的邊與其他邊約束起來的半平面交集會更小
            //所以應當將最後一個邊換成新的邊
            if (onLeft(q[last], narrow[i].p))
                q[last] = narrow[i];
        }
        //求新的交點
        if (first < last)
            intersections[last - 1] = getIntersection(q[last - 1], q[last]);
    }

    //最後要用單調佇列頭端的邊去檢查一下
    //因為first的邊會被後面的邊約束，但尾端的邊不會
    //到此邊們會形成一個環，我們可以用first去約束尾端的邊
    //以此去除多餘的邊
    while (first < last && !onLeft(q[first], intersections[last - 1]))
        --last;
    //last - first <= 1 -> 只有小於等於一個邊，不能形成凸多邊形，所以return 0
    if (last - first <= 1)
        return 0;

    //在這裡其實用不到，但為了邏輯完整而加上，求最後一個邊與第一的邊的交點
    intersections[last] = getIntersection(q[last], q[first]);

    delete[] intersections;
    delete[] q;
    return last - first + 1;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n)
    {
        double x, y;

        for (int i = 0; i < n; ++i)
        {
            scanf("%lf %lf", &x, &y);
            points[i] = Point(x, y);
        }

        //做原本的凸多邊形的邊的參數式
        for (int i = 0; i < n; ++i)
        {
            lines[i].p = points[i];
            lines[i].setDirectionVector(Vector::getDirectionVectorFormPoints(points[i], points[(i + 1) % n]));
            lines[i].normal = Vector::getNormal(lines[i].v);
        }

        //二分搜答案
        double l = 0, r = 10000, mid;
        while ((r - l) > 1e-7)
        {
            mid = (l + r) / 2.0;
            //全部邊內縮mid的距離變narrow
            for (int i = 0; i < n; ++i)
            {
                narrow[i] = Line(lines[i].p + (lines[i].normal * mid), lines[i].v);
            }

            if (halfplaneIntersection(n))
                l = mid;
            else
                r = mid;
        }

        printf("%.6lf\n", l);
    }
    return 0;
}