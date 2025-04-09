#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> numbers;
int visited[100002];

int main(void)
{
    int answer = -1;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }

    int ri = 0;
    int le = 0;
    for (int le = 0; le < n; le++)
    {
        while (ri < n && visited[numbers[ri]] < k)
        {
            visited[numbers[ri]]++;
            ri++;
        }
        answer = max(answer, ri - le);
        if (ri == n)
            break;
        visited[numbers[le]]--;
    }

    cout << answer << endl;
}