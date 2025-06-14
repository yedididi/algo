
// {
//     vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m,0));

//     parent[newI][newJ] = poppedNode;

//     oldI = startI + i;
//     oldJ = startJ + j;

//     //90 clock
//     newI = startI + j;
//     newJ = startJ + (squareSize - 1) - i;

//     //180
//     newI = startI + (squareSize - 1 - i);
//     newJ = startJ + (squareSize - 1 - j);

//     //270
//     newI = startI + (squareSize - 1) - j;
//     newJ = startJ + i;
// }

#include <iostream>
#include <vector>
using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) cout << val << ' ';
        cout << '\n';
    }
    cout << '\n';
}

vector<vector<int>> rotate90(const vector<vector<int>>& mat, int startI, int startJ, int size) {
    vector<vector<int>> res(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int oldI = startI + i;
            int oldJ = startJ + j;
            int newI = startI + j;
            int newJ = startJ + (size - 1) - i;
            res[newI][newJ] = mat[oldI][oldJ];
        }
    }
    return res;
}

vector<vector<int>> rotate180(const vector<vector<int>>& mat, int startI, int startJ, int size) {
    vector<vector<int>> res(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int oldI = startI + i;
            int oldJ = startJ + j;
            int newI = startI + (size - 1 - i);
            int newJ = startJ + (size - 1 - j);
            res[newI][newJ] = mat[oldI][oldJ];
        }
    }
    return res;
}

vector<vector<int>> rotate270(const vector<vector<int>>& mat, int startI, int startJ, int size) {
    vector<vector<int>> res(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int oldI = startI + i;
            int oldJ = startJ + j;
            int newI = startI + (size - 1) - j;
            int newJ = startJ + i;
            res[newI][newJ] = mat[oldI][oldJ];
        }
    }
    return res;
}

int main() {
    // 예시: 5x5 정사각형 배열
    vector<vector<int>> mat = {
        { 1,  2,  3,  4,  5},
        { 6,  7,  8,  9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    int startI = 0, startJ = 0, size = 5;

    cout << "Original:\n";
    printMatrix(mat);

    cout << "90 degrees:\n";
    printMatrix(rotate90(mat, startI, startJ, size));

    cout << "180 degrees:\n";
    printMatrix(rotate180(mat, startI, startJ, size));

    cout << "270 degrees:\n";
    printMatrix(rotate270(mat, startI, startJ, size));

    return 0;
}
