#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int getANum(int startIndex, string input, int bLen)
{
    int ANum = 0;

    for (int i = startIndex; i < startIndex + bLen; i++)
    {
        if (input[i] == 'a')
            ANum++;
    }
    return (ANum);
}

int main(void)
{
    string input;
    int bLen = 0;
    int minNum = 2147483647;

    cin >> input;

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == 'b')
            bLen++;
    }

    string newStr = input + input;

    for (int i = 0; i <= input.length(); i++)
    {
        // cout << "i is:" << i << endl;
        minNum = min(minNum, getANum(i, newStr, bLen));
    }

    cout << minNum << endl;
}

// abababababababa
