#include <iostream>
#include <queue>

using namespace std;

int n;

int main(void)
{
    cin >> n;

    queue<int> q;

    for (int i = 1; i <= n; i++)
        q.push(i);

    while (q.size() != 1)
    {
        q.pop();
        int second = q.front();
        q.pop();
        q.push(second);
    }    
    cout << q.front() << endl;
}