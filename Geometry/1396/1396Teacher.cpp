#include <iostream>
#include <math.h>
#include <Algorithm>

using namespace std;

struct Point
{
    double x, y;
    Point (double x=0.0, double y=0.0): x(x), y(y) { }
};

typedef Point Vector;

struct Line
{
    Point p;
    Vector v;
    double ang;
    Line(Point p, Vector v): p(p), v(v) { ang=atan2(v.y, v.x); }
    Line() {}
    bool operator < (const Line& L) const { return ang<L.ang; }
};

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point  A, Point  B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }

double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y; }
double Length(Vector A) {return sqrt(Dot(A, A));}
double Cross(Vector A, Vector B) { return(A.x*B.y-A.y*B.x); }
bool   OnLeft(Line L, Point p) { return Cross(L.v, p-L.p)>0; }

Vector Normal (Vector A)
{
    double L=Length(A);
    return Vector(-A.y/L, A.x/L);
}

Point GetIntersection(Line a, Line b)
{
    Vector u=a.p-b.p;
    double t=Cross(b.v, u)/Cross(a.v, b.v);
    return a.p+a.v*t;
}

int HalfplaneIntersection(Line* nar, int n, Point* poly)
{
    sort(nar, nar+n);
    int first, last;
    Point *p=new Point[n];
    Line  *q=new Line[n];

    q[first=last=0]=nar[0];

    for (int i=1; i<n; i++)
    {
        while (first<last && !OnLeft(nar[i], p[last-1])) last--;
        while (first<last && !OnLeft(nar[i], p[first])) first++;

        q[++last]=nar[i];
        if (fabs(Cross(q[last].v, q[last-1].v))<1e-7)
        {
            last--;
            if(OnLeft(q[last], nar[i].p)) q[last]=nar[i];
        }
        if (first<last)
            p[last-1]=GetIntersection(q[last-1], q[last]);
    }

    while(first<last && !OnLeft(q[first], p[last-1]))
        last--;
    if (last-first<=1)
        return 0;

    p[last]=GetIntersection(q[last], q[first]);

    int m=0;
    for(int i=first; i<=last; i++)
        poly[m++]=p[i];

    return m;
}

Point  p[200], poly[200];
Line   narrow[200];
Vector v[200], v_normal[200];

int main()
{
    // freopen("d:\\1396_in.txt", "r", stdin);
    // freopen("d:\\1396_out.txt", "w", stdout);
    int n;

    while (scanf("%d", &n)==1 && n)
    {
        int m, x, y;

        for (int i=0; i<n; i++)
        {
            scanf("%d%d", &x, &y);
            p[i]=Point(x, y);
        }

        for (int i=0; i<n; i++)
        {
            v[i]=p[(i+1)%n]-p[i];
            v_normal[i]=Normal(v[i]);
        }

        double l=0, r=10000;

        while ((r-l)>1e-7)
        {
            double mid=l+(r-l)/2;

            for (int i=0; i<n; i++)
                narrow[i]=Line(p[i]+v_normal[i]*mid, v[i]);

            m=HalfplaneIntersection(narrow, n, poly);

            if (!m)
                r=mid;
            else
                l=mid;
        }
        printf("%.6lf\n", l);
    }
    return 0;
}
