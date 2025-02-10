#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   // srand, rand
#include <ctime>     // time

using namespace std;

int main() 
{
    int respA;

    srand(time(0));

    vector<int> randNum(10000);
    for (int i = 0; i < 10000; i++)
        randNum[i] = i + 1;
        
    random_shuffle(randNum.begin(), randNum.end());

    for (int a = 1; a <= 10000; a++)
    {
        std::cout << "? A " << randNum[a] << "\n" << std::flush;
        std::cin >> respA;

        if(respA == 1)
        {
            int respB;
            int ansA = randNum[a];
            for (int i = 0; i < 10000; i++)
                randNum[i] = i + 1;
            random_shuffle(randNum.begin(), randNum.end());

            for (int b = 1; b <= 10000; b++)
            {
                std::cout << "? B " << randNum[b] << "\n" << std::flush;
                std::cin >> respB;
            
                if (respB == 1)
                {
                    int ansB = randNum[b];
                    std::cout << "! " << ansA + ansB << endl;
                    return (0);
                }
            }
            break;
        }
    }
}