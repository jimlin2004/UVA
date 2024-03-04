#include <iostream>
#include <algorithm>
using namespace std;

//基本上是實作一個sort規則

class DNA
{
private:
    string data;
    int inversion = 0;
    int inputIndex = 0;
    void countInversion()
    {
        this->inversion = 0;
        for (int i = 0; i < this->data.size(); ++i)
        {
            for (int j = i + 1; j < this->data.size(); ++j)
            {
                if (this->data[i] > this->data[j])
                    ++this->inversion;
            }
        }
    }
public:
    DNA() = default;

    bool operator < (const DNA& other) const
    {
        if (this->inversion == other.inversion)
            return this->inputIndex < other.inputIndex;
        return this->inversion < other.inversion;
    }

    void setInputIndex(int inputIndex)
    {
        this->inputIndex = inputIndex;
    }

    friend istream& operator>>(istream& input, DNA& obj);
    friend ostream& operator<<(ostream& output, const DNA& obj);
};

istream& operator>>(istream& input, DNA& obj)
{
    input >> obj.data;
    obj.countInversion();
    return input;
}

ostream& operator<<(ostream& output, const DNA& obj)
{
    output << obj.data;
    return output;
}

DNA DNAs[105];

int main()
{
    //會導致輸出異常?
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);

    int t;
    cin >> t;
    int n, m;
    
    bool first = true;

    while (t--)
    {
        cin >> n >> m;
        for (int i = 0; i < m; ++i)
        {
            cin >> DNAs[i];
            DNAs[i].setInputIndex(i);
        }

        sort(DNAs, DNAs + m);

        if (first)
            first = false;
        else
            puts("");

        for (int i = 0; i < m; ++i)
            cout << DNAs[i] << '\n';
    }

    return 0;
}