#include <iostream>

using namespace std;

int n;
int arr[21];
int k;
int printTimes = 0;
bool endVal = false;

void printPermutation(int permutation[21], bool visited[21], int depth)
{
    if (endVal)
        return ;

    if (depth == n)
    {
        printTimes++;
        if (printTimes == k)
        {    
            for (int i = 0; i < n; i++)
                cout << permutation[i] << " ";
            cout << "\n";
            // exit(0); //maybe not possible?
            endVal = true;
            return ;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (visited[i])
            continue;
        
        visited[i] = true;
        permutation[depth] = i;
        printPermutation(permutation, visited, depth + 1);
        visited[i] = false;
    }
}

void printWhichPermutation(int permutation[21], bool visited[21], int depth)
{
    
}

int main(void)
{
    int problemType;
    bool visited[21] = {false, };
    int permutation[21] = {0, };
    cin >> n >> problemType;

    if (problemType == 1)
    {
        cin >> k;
        printPermutation(permutation, visited, 0);
    }
    else if (problemType == 2)
    {
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        printWhichPermutation(permutation, visited, 0);
    }
}