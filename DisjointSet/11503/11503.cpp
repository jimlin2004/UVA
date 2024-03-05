#include <unordered_map>
#include <iostream>
#include <cstring>
using namespace std;

//只是Disjoint set練習

#define maxn 100005

int parent[maxn];

int findRoot(int x)
{
	if (parent[x] < 0)
		return x;
	return parent[x] = findRoot(parent[x]);
}

int Union(int a, int b)
{
	int r1 = findRoot(a);
	int r2 = findRoot(b);
	if (r1 == r2)
		return parent[r1];
	if (parent[r1] < parent[r2])
	{
		parent[r1] += parent[r2];
		parent[r2] = r1;
		return parent[r1];
	}
	else
	{
		parent[r2] += parent[r1];
		parent[r1] = r2;
		return parent[r2];
	}
}

unordered_map<string, int> mp;
int lastID = 0;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		memset(parent, -1, sizeof(parent));
		mp.clear();
		lastID = 0;
		int n;
		cin >> n;
		string a, b;
		while (n--)
		{
			int aID, bID;
			cin >> a >> b;
			if (mp.find(a) == mp.end())
			{
				mp[a] = lastID;
				aID = lastID;
				lastID++;
			}
			else
				aID = mp[a];
			
			if (mp.find(b) == mp.end())
			{
				mp[b] = lastID;
				bID = lastID;
				lastID++;
			}
			else
				bID = mp[b];
				
			printf("%d\n", -Union(aID, bID));
		}
	}
	return 0;
}