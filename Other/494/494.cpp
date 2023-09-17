#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    int count;
    bool flag;
    while (getline(cin, str))
    {
        count = 0;
        flag = false;
        for (char c: str)
        {
            if (!isalpha(c))
            {
                if (flag)
                {
                    count++;
                    flag = false;
                }
            }
            else
            {
                flag = true;
            }
        }
        if (flag)
            count++;
        cout << count << '\n';
    }
    
    // system("pause");
    return 0;
}