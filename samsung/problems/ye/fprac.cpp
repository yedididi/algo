//예술성
#include <iostream>

using namespace std;

int main(void)
{
    for (int i = 0; i < squareSize; i++)
    {
        for (int j = 0; j < squareSize; j++)
        {
            int oldI = startI + i;
            int oldJ = startJ + j;
            int newI = startI + j;
            int newJ = startJ + (squareSize - 1) - i;

            newMap[newI][newJ] = oldMap[oldI][oldJ];
        }
    }
}

