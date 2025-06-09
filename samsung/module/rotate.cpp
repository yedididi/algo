#include <iostream>
using namespace std;

int main() {
    const int N = 5;
    int map[N][N] = {0};
    
    // 첫 번째 열을 1로 초기화
    for (int i = 0; i < N; i++) {
        map[i][0] = 1;
    }

    // 원본 배열 출력
    cout << "Original map:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    // 90도 시계 방향 회전
    int newMap[N][N] = {0};

    int start_x = 0, end_x = N;
    int start_y = 0, end_y = N;

    for (int i = start_x; i < end_x; i++) {
        for (int j = start_y; j < end_y; j++) {
            newMap[start_x + (j - start_y)][(end_y - 1) - (i - start_x)] = map[i][j];
        }
    }

    // 회전된 배열 출력
    cout << "\nRotated map (90 degrees clockwise):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << newMap[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
