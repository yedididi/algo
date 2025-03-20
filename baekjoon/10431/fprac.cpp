#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getSteps(void)
{
    int steps = 0;
    int studentNum = 0;

    vector<int> students(20, 0);

    for (int i = 0; i < 20; i++)
    {
        cin >> students[studentNum];
        
        for (int index = studentNum - 1; index >= 0; index--)
        {
            if (students[index] > students[index + 1])
            {
                swap(students[index], students[index + 1]);
                steps++;
            }
            else
                break;
        }
        studentNum++;
    }
    return (steps);
}

int main(void)
{
    int n;
    vector<int> steps;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        steps.push_back(getSteps());
    }

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << " " << steps[i] << "\n";
    }
}