#include <string>
#include <iostream>
using namespace std;

bool isSubChar(int& j, const string& encodedStr, char target)
{
    for (int i = j + 1; i < encodedStr.size(); ++i)
    {
        if (encodedStr[i] == target)
        {
            j = i;
            return true;
        }
    }
    return false;
}

int main()
{
    string orgStr, encodedStr;
    bool no;
    while (cin >> orgStr >> encodedStr)
    {
        int j = -1; // for first index
        no = false;
        for (int i = 0; i < orgStr.size(); ++i)
        {
            if (!isSubChar(j, encodedStr, orgStr[i]))
            {
                no = true;
                printf("No\n");
                break;
            }
        }
        if (!no)
            printf("Yes\n");
    }
    return 0;
}