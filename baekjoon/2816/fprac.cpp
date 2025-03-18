#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n;
vector<string> channels;

int main(void)
{
    string target = "KBS1";
    int targetNum = 0;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        channels.push_back(tmp);
    }

    while (1)
    {
        for (int i = 0; i < n; i++)
        {
            if (channels[i] == target)
            {
                for (int j = i; j >= targetNum; j--)
                {
                    if (j == targetNum)
                    {
                        break;
                    }
                    cout << "4";
                    string tmp = channels[j];
                    channels[j] = channels[j - 1];
                    channels[j - 1] = tmp;
                }
                target = "KBS2";
                targetNum++;
                break;
            }
            cout << "1";
        }
        if (targetNum == 2)
            break;
    }
    cout << endl;
}