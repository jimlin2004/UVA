#include <bits/stdc++.h>
using namespace std;

/*
    題意:
        兩個人分別搭不同線的火車，兩輛火車都會過A城市
        一列在(t1, t2)的時間內進A城市，
        另一列在(s1, s2)的時間內進A城市，
        火車都只會留w時間
        問兩個人碰面的機率(火車停靠時間重疊)的機率?
    
    這題是幾何題

    將時間轉成二維平面
    1. t1 <= x <= t2
    2. s1 <= y <= s2
    這可以結合出一個二維的長方形

    碰面的條件轉成二維平面
    | x - y | <= w
    -> -w <= x - y or x - y <= w
    -> 兩個斜直線的一邊半平面 
       x - y + w = 0 右半平面
       x - y - w = 0 左半平面
    
    此時所問的碰面區間就是兩個半平面相交，又同時與長方形相交的面積
    (看推導1.png)
    
    機率 P = (長方形與半平面相交面積) / 長方形總面積

    至此問題難點剩下碰面區域面積的計算

    兩個直線與長方形相交的情況有7種
    (看推導2 ~ 8.png)

    簡化處理，
    碰面區域面積 就是 x -y-w=0 的左上矩形面積 - x-y+w=0的左上方矩形面積

    此時問題剩下一條斜率=1的直線的左上矩形面積
    一樣有多種狀況要討論
    (看推導9 ~ 14.png)
*/


double t1, t2, s1, s2;
double width, height;


// 求直線x-y+w=0左上平面與矩形(s1, t1) ~ (s2, t2)的相交面積
double getArea(double w)
{


    // 下方四點是帶入直線方程式求得
    double ly = t1 + w;
    double ry = t2 + w;
    double tx = s2 - w;
    double bx = s1 - w;

    bool onLeft   = (s1 <= ly) && (ly <= s2); // 左邊有交點
    bool onRight  = (s1 <= ry) && (ry <= s2); // 右邊有交點
    bool onTop    = (t1 <= tx) && (tx <= t2); // 上邊有交點
    bool onBottom = (t1 <= bx) && (bx <= t2); // 下邊有交點

    if (onLeft && onRight)   // case 1
        return (s2 - ly + s2 - ry) * width * 0.5; // 梯形面積
    if (onLeft && onTop)     // case 2
        return (s2 - ly) * (tx - t1) * 0.5; // 三角形面積
    if (onTop && onBottom)   // case 3
        return (bx - t1 + tx - t1) * height * 0.5; // 梯形面積
    if (onRight && onBottom) // case 4
        return height * width - (t2 - bx) * (ry - s1) * 0.5; // 用矩形 - 三角形面積
    
    // case 5(1) or case 5(2)
    return (ly <= s1) ? width * height : 0; // 整個矩形或是整個沒有相交
}


int main()
{
    int T;
    scanf("%d", &T);
    for (int testcase = 1; testcase <= T; ++testcase)
    {
        double w;
        scanf("%lf %lf %lf %lf %lf", &t1, &t2, &s1, &s2, &w);
        
        width  = t2 - t1;
        height = s2 - s1;
        
        double area1 = getArea(w);  // x-y+w=0
        double area2 = getArea(-w); // x-y-w=0

        printf("Case #%d: %.6lf\n", testcase, (area2 - area1) / width / height);
    }

    return 0;
}