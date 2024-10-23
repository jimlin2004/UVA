#include <cstdio>
#include <algorithm>
using namespace std;

//找公式

int main()
{
	long long n, m;
	while (scanf("%lld %lld", &m, &n) && m && n)
	{
		//如果有一個邊只有一個就要額外處理
		if (m == 1)
		{
			printf("%lld\n", ((n - 1 + 1) * (n - 1)) / 2 * 2);
			continue;
		}
		if (n == 1)
		{
			printf("%lld\n", ((m - 1 + 1) * (m - 1)) / 2 * 2);
			continue;
		}
		//算斜對角的答案數
		long long dia = 0;
		//min_ = 最小的邊
		long long min_ = min(m, n);
		//還沒到中間都一樣之前的斜對角且只算一邊，另一半後面會乘上去
		for (long long i = 2; i < min_; ++i)
			dia += (i - 1 + 1) * (i - 1) / 2;
		//如果是方陣，其實後面發現不用額外處理，公式都一樣
		if (m == n)
		{
			dia = dia * 2 + (min_ - 1 + 1) * (min_ - 1) / 2;
		}
		//如果是長方形且min_是奇數還是偶數，後面發現公式都一樣
		else if (min_ % 2 == 0)
			dia = dia * 2 + (max(m, n) - min(m, n) + 1) * (min_ - 1 + 1) * (min_ - 1) / 2;
		else
			dia = dia * 2 + (max(m, n) - min(m, n) + 1) *(min_ - 1 + 1) * (min_ - 1) / 2;
		//算橫的row有多少
		long long row = ((m - 1 + 1) * (m - 1)) / 2;
		row *= n;
		//算直的col有多少
		long long col = ((n - 1 + 1) * (n - 1)) / 2;
		col *= m;
		//dia記得乘2，因為上面的dia只有算左上到右下的數量
		//全部要乘2，因為兩個queen可交換
		printf("%lld\n", 2 * (2 * dia + row + col));
	}
	return 0;
}