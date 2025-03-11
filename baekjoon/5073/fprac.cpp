#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    while (1)
    {
        vector<int> numbers(3, 0);

        cin >> numbers[0] >> numbers[1] >> numbers[2];

        if (numbers[0] == 0)
            break;
        
        sort(numbers.begin(), numbers.end());
        
        if (numbers[2] >= (numbers[0] + numbers[1]))
            cout << "Invalid\n";
        else if (numbers[2] == numbers[0])
            cout << "Equilateral\n";
        else if (numbers[2] == numbers[1])
            cout << "Isosceles\n";
        else
            cout << "Scalene\n";
    }
}