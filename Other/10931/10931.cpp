#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    int I;
    bool flag;
    while (scanf("%d", &I))
    {
        if (I == 0)
            break;
        flag = false;
        cout << "The parity of ";
        bitset<32> bits(I);
        for (int i = bits.size() - 1; i >= 0; i--)
        {
            if (flag)
                cout << bits[i];
            else
            {
                if (bits[i] != 0)
                {
                    cout << bits[i];
                    flag = true;
                }
            }
        }
        cout << " is " << bits.count() << " (mod 2).\n";
    }
}