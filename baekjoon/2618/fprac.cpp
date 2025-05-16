#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, w;
vector<int> answer;

int main(void)
{
    int oneI = 1, oneJ = 1;
    cin >> n >> w;
    int twoI = n, twoJ = n;
    int dist = 0;

    for (int i = 0; i < w; i++)
    {
        int caseI, caseJ;

        cin >> caseI >> caseJ;

        int oneDist = abs(caseI - oneI) + abs(caseJ - oneJ);
        int twoDist = abs(caseI - twoI) + abs(caseJ - twoJ);

        if (oneDist > twoDist)
        {
            // cout << "dist:" <<  twoDist << endl;
            dist += twoDist;
            answer.push_back(2);
            twoI = caseI;
            twoJ = caseJ;
        }
        else
        {
            // cout << "dist:" << oneDist << endl;
            dist += oneDist;
            answer.push_back(1);
            oneI = caseI;
            oneJ = caseJ;
        }
    }

    cout << dist << "\n";
    for (vector<int>::iterator itr = answer.begin(); itr != answer.end(); itr++)
    {
        cout << *itr << "\n";
    }
}