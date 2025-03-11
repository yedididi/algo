#include <iostream>

#define n 4
#define r 3

using namespace std;

int cArr[r] = { 0, };
int pArr[r] = { 0, };
bool check[n + 1] = { false, }; 

void printArray(int arr[r])
{
    for (int i = 0; i < r; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void permutation(int depth)
{
    if (depth == r)
    {
        printArray(pArr);
        return;
    }
    
    for (int i = 1; i <= n; i++)
    {
        if (!check[i])
        {
            check[i] = true;
            pArr[depth] = i;
            permutation(depth + 1);
            check[i] = false;
        }
    }
}

void combination(int depth, int next)
{
    if(depth == r)
    {
        printArray(cArr);
        return;
    }

    for(int i = next; i <= n; i++)
    {
        cArr[depth] = i;
        combination(depth + 1, i + 1);
    }
}

int main(void)
{
    cout << "조합 (순서x, 중복x)" << endl;
    combination(0, 1);

    return 0;
}