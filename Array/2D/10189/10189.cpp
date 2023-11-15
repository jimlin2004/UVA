#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int grid[105][105];
int n, m;

int direction[8][2] = {
	{1,0}, {1,1}, {0,1}, {-1,1},
	{-1,0}, {-1,-1}, {0,-1}, {1,-1}
};

inline bool check(int i, int j)
{
	return (i >= 1) && (i <= n) && (j >= 1) && (j <= m) && (grid[i][j] != -1);	
}

int main()
{
//	freopen("./input.txt", "r", stdin);
//	freopen("./output.txt", "w", stdout);
	
	int Case = 0;
	bool first = true;
	while (scanf("%d %d", &n, &m) != EOF && n && m)
	{
		memset(grid, 0, sizeof(grid));
		char input;
		int x, y;
		getchar(); //for \n
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= m; ++j)
			{
				scanf("%c", &input);
				if (input == '*')
				{
					grid[i][j] = -1;
					for (int d = 0; d < 8; ++d)
					{
						x = j + direction[d][0];
						y = i + direction[d][1];
						if (check(y, x))
							++grid[y][x];
					}
				}
			}
			getchar(); // for \n
		}
		
		if (first)
			first = false;
		else
			puts("");
			
		printf("Field #%d:\n", ++Case);
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= m; ++j)
			{
				if (grid[i][j] == -1)
					putchar('*');
				else
					printf("%d", grid[i][j]);	
			}
			puts("");
		}
	}
	return 0;
} 
