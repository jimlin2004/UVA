#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int queens[10];
int fixedQ;
int count;

inline bool isCollision(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) == abs(y1 - y2));	
}

void backtracking(int c)
{
	if (c == fixedQ)
	{
		backtracking(c + 1);
		return;
	}
		
	if (c == 9)
	{
		printf("%2d      ", ++count);
		printf("%d", queens[1]);
		for (int i = 2; i <= 8; ++i)
			printf(" %d", queens[i]);
		puts("");
		return;
	}
	
	bool ok;
	for (int i = 1; i <= 8; ++i)
	{
		ok = true;
		for (int j = 1; j < c; ++j)
		{
			if (isCollision(c, i, j, queens[j]) || i == queens[j])
			{
				ok = false;
				break;
			}	
		}
		
		if (isCollision(fixedQ, queens[fixedQ], c, i) || i == queens[fixedQ])
			ok = false;
		
		if (ok)
		{
			queens[c] = i;
			backtracking(c + 1);
		}
	}
}

int main()
{
//	freopen("./input.txt", "r", stdin);
//	freopen("./out.txt", "w", stdout);
	int t;
	cin >> t;
	int r, c;
	bool first = true;
	while (t--)
	{
		memset(queens, 0, sizeof(queens));
		count = 0;
		cin >> r >> c;
		queens[c] = r;
		fixedQ = c;
		if (first)
			first = false;
		else
			puts("");
		puts("SOLN       COLUMN");
		puts(" #      1 2 3 4 5 6 7 8");
		puts("");
		backtracking(1);
	}
	return 0;
}