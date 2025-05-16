#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int n;
map<int, int> coorInOrder;
map<int, int>::iterator highest;

int increasingShape()
{
    int area = 0;
    int beforeHeight = 0;
    int beforeCoor = 0;

    for (map<int, int>::iterator itr = coorInOrder.begin(); itr != coorInOrder.end(); itr++)
    {
        // cout << "this is area:" << area << endl;
        if (itr->second < beforeHeight)
            continue;
        if (itr != coorInOrder.begin())
            area = area + (itr->first - beforeCoor) * beforeHeight;
        beforeHeight = itr->second;
        beforeCoor = itr->first;
        highest = itr;
    }
    return (area);
}

int decreasingShape()
{
    int area = 0;
    int beforeCoor = 0;
    int beforeHeight = 0;

    for (map<int, int>::iterator itr = --coorInOrder.end(); itr != highest; itr--)
    {
        if (itr->second < beforeHeight)
            continue;
        if (beforeCoor != 0)
            area = area + (beforeCoor - itr->first) * beforeHeight;
        beforeCoor = itr->first;
        beforeHeight = itr->second;
        // cout << beforeCoor << " " <<  highest->first << " " << beforeHeight << endl;
        // cout << itr->second << ", area is:" << area << endl;
    }
    return (area + ((beforeCoor - highest->first) * beforeHeight));
}

int main(void)
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int coor, hei;

        cin >> coor >> hei;
        coorInOrder.insert({coor, hei});
    }

    // cout << increasingShape() << endl;
    // cout << decreasingShape() << endl;
    cout << increasingShape() + decreasingShape() + highest->second << endl;
}

// 7
// 2 4
// 11 4
// 15 3
// 4 6
// 5 3
// 8 10
// 13 6

// 4
// 11 4
// 15 3
// 8 10
// 13 6