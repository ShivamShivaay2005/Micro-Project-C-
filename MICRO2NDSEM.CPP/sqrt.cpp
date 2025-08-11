#include <iostream>
using namespace std;

class Solution
{
public:
    int mySqrt(int x)
    {
        int sqrt = 0;
        for (int i = x; i > 0; i--)
        {
            if (i * i == x)
            {
                sqrt = i;
                return sqrt;
            }
        }
        return sqrt;
    }
};

int main()
{
    Solution s1;
    int n = s1.mySqrt(2);
    cout << "sqrt: " << n << endl;

    return 0;
}