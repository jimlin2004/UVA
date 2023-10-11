#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct Segment
{
	int d, l, r;
	bool operator < (const Segment& other)
	{
		return this->d < other.d;
	}
} segments[5005];

int n;

int check(double x)
{
	double L = atan2(segments[0].d, segments[0].r - x);
	double R = atan2(segments[0].d, segments[0].l - x);
	
	for (int i = 1; i < n; ++i)
	{
		double l = atan2(segments[i].d, segments[i].r - x);
		double r = atan2(segments[i].d, segments[i].l - x);
		
		if (L - r > 1e-6)
			return -1;
		if (l - R > 1e-6)
			return 1;
		
		L = max(L, l);
		R = min(R, r);
	}
	return 0;
}

int main()
{
	int t;
	double w;
	
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lf", &w);
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d %d %d", &segments[i].d, &segments[i].l, &segments[i].r);
		}
		sort(segments, segments + n);
		
		bool ok = false;
		double l = 0, r = w;
		while ((r - l) > 1e-6)
		{
			double mid = (l + r) / 2.0;
			int k = check(mid);
			if (k == 1)
				l = mid;
			else if (k == -1)
				r = mid;
			else
			{
				ok = true;
				break;
			}
		}
		if (ok)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}