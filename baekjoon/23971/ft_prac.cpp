#include <iostream>

using namespace std;

int h, w, n, m;

int main(void)
{
    int total = 0;

    cin >> h >> w >> n >> m;

    if (h % (n + 1) == 0)
        total = (h / (n + 1));
    else
        total = (h / (n + 1)) + 1;

    
    if (w % (m + 1) == 0)
        total *= (w / (m + 1));
    else
        total *= ((w / (m + 1)) + 1);
        
    cout << total << endl;
}
