#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

/*
核心概念:
	題目要找出所有圖中的環，反過來想
	當作出圖的生成樹時，再加入一條邊一定會環
	而題目就是要求那些會讓生成樹出現環的邊加起來權重最小
	所以解法就是建出一棵最大生成樹，
	則totalCost - 最大生成樹的cost = 會出現環的權重總和(最小，不唯一)
*/

struct Edge
{
	int u, v, w;
	bool operator < (const Edge& other) const
	{
		return this->w > other.w;	
	}
};

int n, m;

int parent[10005];
vector<Edge> edges;

int findRoot(int x)
{
	if (parent[x] < 0)
		return x;
	return parent[x] = findRoot(parent[x]);
}

bool Union(int x, int y)
{
	int r1 = findRoot(x);
	int r2 = findRoot(y);
	if (r1 == r2)
		return false;
	if (parent[r1] < parent[r2])
	{
		parent[r1] += parent[r2];
		parent[r2] = r1;
	}
	else
	{
		parent[r2] += parent[r1];
		parent[r1] = r2;
	}
	return true;
}

int kurskal()
{
	memset(parent, -1, sizeof(parent));
	
	sort(edges.begin(), edges.end());
	int res = 0;
	int count = 0;
	for (Edge& edge: edges)
	{
		if (Union(edge.u, edge.v))
		{
			res += edge.w;
			++count;
		}
		
		if (count == n - 1)
			return res;
	}
	
	return res;
}

 
int main()
{
	int t;
	while (scanf("%d", &t) != EOF && t)
	{
		while (t--)
		{
			scanf("%d %d", &n, &m);
			
			edges.clear();
			int totalCost = 0;
			int u, v, w;
			for (int i = 0; i < m; ++i)
			{
				scanf("%d %d %d", &u, &v, &w);
				totalCost += w;
				edges.emplace_back(Edge{u, v, w});
				edges.emplace_back(Edge{v, u, w});
			}
			
			printf("%d\n", totalCost - kurskal());
		}
	}
	
	return 0;
}