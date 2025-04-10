// #include <iostream>
// #include <vector>
// #include <set>

// using namespace std;

// int n, d, k, c;
// vector<int> sushi;
// multiset<int> visited;
// int maxNum = -1;

// int main(void)
// {
//     int size = 0;
//     bool flag = false;
//     cin >> n >> d >> k >> c;

//     for (int i = 0; i < n; i++)
//     {
//         int tmp;
//         cin >> tmp;
//         sushi.push_back(tmp);
//     }

//     for (int i = 0; i < n; i++)
//         sushi.push_back(sushi[i]);


//     int left = 0;
//     int right = k - 1;

//     while (1)
//     {
//         set<int> visited_set(sushi.begin() + left, sushi.begin() + right + 1);
//         size = visited_set.size();
//         if (visited_set.find(c) == visited_set.end())
//             size++;
//         maxNum = max(maxNum, size);

//         left = left + 1;
//         right = right + 1;

//         if (left == n)
//             break;
//     }

//     cout << maxNum << endl;
// }

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, d, k, c;
vector<int> sushi;
int cnt[3001] = {0};

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> d >> k >> c;
    sushi.resize(n);

    for (int i = 0; i < n; i++)
        cin >> sushi[i];

    int unique = 0;

    // First window
    for (int i = 0; i < k; i++) 
    {
        if (cnt[sushi[i]]++ == 0) 
            unique++;
    }

    int maxSushi = unique + (cnt[c] == 0 ? 1 : 0);

    for (int i = 1; i < n; i++) 
    {
        // Remove left
        if (--cnt[sushi[i - 1]] == 0) 
            unique--;
        // Add right
        int newIdx = (i + k - 1) % n;
        if (cnt[sushi[newIdx]]++ == 0)
            unique++;

        int total = unique + (cnt[c] == 0 ? 1 : 0);
        maxSushi = max(maxSushi, total);
    }

    cout << maxSushi << '\n';
}
