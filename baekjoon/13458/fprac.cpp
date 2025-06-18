#include <iostream>
#include <vector>

using namespace std;

long long n, b, c;
vector<long long> students;

void input(void)
{
    cin >> n;
    students.resize(n, 0);

    for (long long i = 0; i < n; i++)
        cin >> students[i];
    
    cin >> b >> c;
}

int main(void)
{   
    long long teacherNum = 0;

    input();

    for (auto itr = students.begin(); itr != students.end(); itr++)
    {
        long long studentNum = *itr;

        studentNum -= b;
        teacherNum++;
        if (studentNum > 0)
        {
            if (studentNum % c)
                teacherNum += (studentNum / c) + 1;
            else    
                teacherNum += (studentNum / c);
        }
    }
    cout << teacherNum << endl;
}