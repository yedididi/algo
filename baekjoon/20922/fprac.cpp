#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    int n, k;
    vector<int> numbers;
    int visited[100002] = {0};
    int answer = -1;

    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }

    int right = 0;
    int left = 0;
    for (int left = 0; left < n; left++)
    {
        while (right < n && visited[numbers[right]] < k)
        {
            visited[numbers[right]]++;
            right++;
        }
        answer = max(answer, right - left);
        if (right == n)
            break;
        visited[numbers[left]]--;
    }

    cout << answer << endl;
}