#include <iostream>
using namespace std;

int count;

bool test(long long num)
{
    ++count;
    if (num == 9)
        return true;
    if (num < 9)
        return false;
    long long digitSum = 0;
    while(num)
    {
        digitSum += num % 10;
        num /= 10;
    }
    return test(digitSum);
}

int main()
{
    string num;
    while (cin >> num && num[0] != '0')
    {
        count = 0;
        long long digitalSum = 0;
        for (int i = num.size() - 1; i >= 0; --i)
        {
            digitalSum += (num[i] - '0');
        }
        bool ok = test(digitalSum);
        
        cout << num;
        if (ok)
            cout << " is a multiple of 9 and has 9-degree " << count << ".\n";
        else
            cout << " is not a multiple of 9.\n";
    }
}