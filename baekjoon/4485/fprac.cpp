#include <iostream>
#include <queue>

using namespace std;

int n;
int map[130][130];
int minValue = 2147483648;

typedef struct s_node
{
    int i;
    int j;
    int sum;
} t_node;

void getMinRupy(int depth)
{

    
}

int main(void)
{
    while (1)
    {
        cin >> n;

        if (n == 0)
            break;
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int tmp;
                
                cin >> tmp;
                map[i][j] = tmp;
            }
        }
        minValue = 2147483648;
        getMinRupy(0);
        cout << minValue << "\n";
    }
}
