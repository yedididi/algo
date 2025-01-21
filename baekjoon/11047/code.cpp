#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> coins;

int main(void)
{
    int coinNum = 0;
    int biggestCoin;

    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (k >= tmp)
        {
            coins.push_back(tmp);
            biggestCoin = tmp;
        } 
    }

    while (1)
    {
        if (k == 0)
            break;

        if (k - biggestCoin >= 0)
        {
            k -= biggestCoin;
            coinNum++;
        }
        else
        {
            coins.pop_back();
            biggestCoin = *(coins.end());
        }
    }
    cout << coinNum << endl;
}