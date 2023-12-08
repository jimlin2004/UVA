#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

bool isNotPrime[1000005];
vector<int> primes;
vector<long long> factor, exponential;
vector<long long> nums;

void getPrimes()
{
	isNotPrime[0] = isNotPrime[1] = true;
	for (long long i = 2; i <= 1000000; ++i)
	{
		if (!isNotPrime[i])
		{
			primes.emplace_back(i);
			for (long long j = i * i; j <= 1000000; j += i)
			{
				isNotPrime[j] = true;
			}
		}
	}
}

void dfs(int index, long long p)
{
	if (index == factor.size() - 1)
	{
		nums.push_back(p);
		return;
	}
	for (int i = 0; i <= exponential[index]; ++i)
	{
		dfs(index + 1, p);
		p *= factor[index];
	}
}

long long gcd(long long a, long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

long long lcm(long long a, long long b)
{
	return (a / gcd(a, b)) * b;
}


int main()
{
	getPrimes();
	long long n;
	int Case = 1;
	while (scanf("%lld", &n) && n)
	{
		factor.clear();
		exponential.clear();
		
		long long remain = n;
		for (int i = 0; i < primes.size(); ++i)
		{
			if (remain % primes[i] == 0)
			{
				factor.push_back(primes[i]);
				exponential.push_back(0);
				while ((remain % primes[i]) == 0)
				{
					++exponential[exponential.size() - 1];
					remain /= primes[i];
				}
			}
		}
		if (n > 1)
		{
			factor.push_back(n);
			exponential.push_back(1);
		}
		
		nums.clear();
		
		dfs(0, 1);
		
		sort(nums.begin(), nums.end());
		
		bool hasOutput = false;
		printf("Scenario %d:\n", Case++);
		for (int i = 0; i < nums.size(); ++i)
		{
            if (nums[i] > 1000000)
                break;
			for (int j = i + 1; j < nums.size(); ++j)
			{
				if (nums[j] - nums[i] >= 25)
					break;
                if (nums[j] > 1000000)
                    break;
				for (int k = j + 1; k < nums.size(); ++k)
				{
					if (nums[k] - nums[i] > 25)
						break;
                    if (nums[k] > 1000000)
                        break;
					long long _lcm = lcm(nums[i], nums[j]);
					_lcm = lcm(_lcm, nums[k]);
					if (_lcm == n)
					{
						hasOutput = true;
						printf("%lld %lld %lld\n", nums[i], nums[j], nums[k]);
					}
				}
			}
		}
		if (!hasOutput)
		{
			printf("Such bells don't exist\n");
		}
		puts("");
	}
	return 0;
}