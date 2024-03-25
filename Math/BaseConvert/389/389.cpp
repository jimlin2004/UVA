#include <iostream>
using namespace std;

int word[] = {
    '0', '1', '2','3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
};

int convertToDec(const string& str, int base)
{
    int res = 0;
    int b = 1;
    for (int i = str.size() - 1; i >= 0; --i)
    {
        for (int j = 0; j < 16; ++j)
        {
            if (word[j] == str[i])
            {
                res += j * b;
                b *= base;
                break;
            }
        }
    }
    return res;
}

string convertBase(int n, int base)
{
    if (n == 0)
        return "0";
    string res = "";
    while (n)
    {
        res += word[(n % base)];
        n /= base;
    }
    return res;
}

int main()
{
    string input;
    int srcBase;
    int dstBase;
    while (cin >> input >> srcBase >> dstBase)
    {
        int dec = convertToDec(input, srcBase);
        string res = convertBase(dec, dstBase);
        if (res.size() > 7)
            cout << "  ERROR" << '\n';
        else
        {
            for (int i = 7 - res.size() - 1; i >= 0; --i)
                cout << ' ';
            for (int i = res.size() - 1; i >= 0; --i)
            {
                cout << res[i];
            }
            cout << '\n';
        }
    }
    return 0;
}