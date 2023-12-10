#include <iostream>
using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        int k, w;
        cin >> k >> w;
        string totalStr;
        string input;
        cin >> totalStr;
        --w;
        bool same = true;
        while (w--)
        {
            cin >> input;
            int start = totalStr.size() - input.size();
            bool same;
            int j;
            for (int i = start; i < totalStr.size(); ++i)
            {
                same = true;
                for (j = 0; i + j < totalStr.size(); ++j)
                {
                    if (totalStr[i + j] != input[j])
                    {
                        same = false;
                        break;
                    }
                }
                if (same)
                    break;
            }
            
            for (j; j < input.size(); ++j)
                totalStr += input[j];
        }
        cout << totalStr.size() << '\n';
    }
    return 0;
}