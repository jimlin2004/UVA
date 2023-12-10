#include <iostream>
#include <vector>
#include <string>
using namespace std;

//會溢位QQ

int main()
{
    string input;
    vector<unsigned int> nums;
    while (getline(cin, input))
    {
        nums.clear();
        for (int i = 0; i < input.size(); ++i)
        {
            if (!isalnum(input[i]))
                continue;

            if (isalpha(input[i]))
            {
                if (isupper(input[i]))
                {
                    nums.emplace_back(input[i] - 'A' + 10);
                }
                else
                {
                    nums.emplace_back(input[i] - 'a' + 26 + 10);
                }
            }
            else
                nums.emplace_back(input[i] - '0');
        }

        bool ok;
        for (unsigned int base = 2; base <= 62; ++base)
        {
            ok = true;
            unsigned long long total = 0;
            unsigned long long baseNow = 1; 
            for (unsigned int num: nums)
            {
                if (base <= num)
                {
                    ok = false;
                    break;
                }
                total += num * baseNow;
                baseNow *= base;
            }
            if (!ok)
                continue;
            if (total % (base - 1) != 0)
            {
                ok = false;
                continue;
            }
            printf("%u\n", base);
            break;
        }
        if (!ok)
            printf("such number is impossible!\n");
    }
    return 0;
}