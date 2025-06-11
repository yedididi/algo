#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm> // for std::max and std::min

void printMap();

using namespace std;

// 포탑 정보를 담는 구조체
typedef struct s_node
{
    int i, j;
    int attackPoint;
    int lastAttackTime;    // 마지막 공격 시점
    int lastAttackedTime;  // 마지막 공격받은 시점

    s_node(int i_ = 0, int j_ = 0, int attackPoint_ = 0, int lastAttackTime_ = 0, int lastAttackedTime_ = 0)
        : i(i_), j(j_), attackPoint(attackPoint_), lastAttackTime(lastAttackTime_), lastAttackedTime(lastAttackedTime_) {}

    // 공격자 선택을 위한 비교 연산자 (우선순위 큐에 사용)
    // 공격력 낮은 순 -> 마지막 공격 시점 오래된 순 -> (i+j) 큰 순 -> j 큰 순
    bool operator<(const s_node newNode) const
    {
        if (this->attackPoint != newNode.attackPoint)
            return (this->attackPoint > newNode.attackPoint); // 공격력이 낮을수록 우선순위 높음
        if (this->lastAttackTime != newNode.lastAttackTime)
            return (this->lastAttackTime < newNode.lastAttackTime); // lastAttackTime이 작을수록(오래될수록) 우선순위 높음
        if ((this->i + this->j) != (newNode.i + newNode.j))
            return ((this->i + this->j) < (newNode.i + newNode.j)); // (i+j) 값이 클수록 우선순위 높음
        return (this->j < newNode.j); // j 값이 클수록 우선순위 높음
    }
} t_node;

// 피격자 선택을 위한 비교 연산자 (우선순위 큐에 사용)
// 공격력 높은 순 -> 마지막 공격 시점 최근 순 -> (i+j) 작은 순 -> j 작은 순
struct maxComp
{    
    bool operator()(const s_node a, const s_node b) const
    {
        if (a.attackPoint != b.attackPoint)
            return (a.attackPoint < b.attackPoint); // 공격력이 높을수록 우선순위 높음
        if (a.lastAttackTime != b.lastAttackTime)
            return (a.lastAttackTime > b.lastAttackTime); // lastAttackTime이 클수록(최근일수록) 우선순위 높음
        if ((a.i + a.j) != (b.i + b.j))
            return ((a.i + a.j) > (b.i + b.j)); // (i+j) 값이 작을수록 우선순위 높음
        return (a.j > b.j); // j 값이 작을수록 우선순위 높음
    }
};

int n, m, k, globalTime;
int potapNum = 0; // 살아있는 포탑의 개수
int iNum[4] = {0, 1, 0, -1}; // 레이저 공격 시 4방향 (우, 하, 좌, 상)
int jNum[4] = {1, 0, -1, 0};
vector<vector<t_node>> map;

// 초기 입력 처리
void input(void)
{
    cin >> n >> m >> k;

    map.resize(n, vector<t_node>(m)); // N x M 크기로 맵 초기화

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int tmp;
            cin >> tmp;

            if (tmp > 0) {
                potapNum++; // 살아있는 포탑 개수 증가
            }
            map[i][j] = {i, j, tmp, 0, 0}; // 포탑 정보 초기화
        }
    }
}

// 맵 상태 출력 (디버깅용)
void printMap()
{
    cout << "Current Map State (Time: " << globalTime << ", Alive Towers: " << potapNum << "):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << map[i][j].attackPoint << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// 공격자 선택
pair<int, int> chooseAttacker(void)
{
    priority_queue<t_node> pq; // s_node의 operator<를 사용하여 정렬

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j].attackPoint > 0) // 공격력이 0보다 큰 포탑만 고려
                pq.push(map[i][j]);
        }   
    }
    
    pair<int, int> attacker = make_pair(pq.top().i, pq.top().j);
    map[attacker.first][attacker.second].attackPoint += (n + m); // 공격력 증가
    map[attacker.first][attacker.second].lastAttackTime = globalTime; // 마지막 공격 시간 업데이트
    return (attacker);
}

// 피격자 선택
pair<int, int> chooseAttackee(void)
{
    priority_queue<t_node, vector<t_node>, maxComp> pq; // maxComp를 사용하여 정렬

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j].attackPoint > 0) // 공격력이 0보다 큰 포탑만 고려
                pq.push(map[i][j]);
        }
    }

    pair<int, int> attackee = make_pair(pq.top().i, pq.top().j);
    return (attackee);
}

// 레이저 공격 시도 (BFS를 통한 최단 경로 탐색)
bool tryLaserAttack(pair<int, int> attacker, pair<int, int> attackee)
{
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1})); // 경로 추적을 위한 부모 노드 저장

    visited[attacker.first][attacker.second] = true;
    q.push({attacker.first, attacker.second});

    bool pathFound = false;

    while (!q.empty())
    {
        pair<int, int> poppedNode = q.front();
        q.pop();

        if (poppedNode.first == attackee.first && poppedNode.second == attackee.second)
        {
            pathFound = true;
            break; // 피격자에 도달했으므로 경로 탐색 종료
        }

        for (int index = 0; index < 4; index++) // 상하좌우 4방향 이동
        {
            int newI = (poppedNode.first + iNum[index] + n) % n; // 맵 경계 처리
            int newJ = (poppedNode.second + jNum[index] + m) % m; // 맵 경계 처리

            if (map[newI][newJ].attackPoint <= 0) continue; // 부서진 포탑으로는 이동 불가
            if (visited[newI][newJ]) continue; // 이미 방문한 곳은 다시 방문하지 않음
            
            q.push({newI, newJ});
            visited[newI][newJ] = true;
            parent[newI][newJ] = poppedNode; // 부모 노드 저장
        }
    }

    if (pathFound)
    {
        // 공격력 계산 및 lastAttackedTime 업데이트
        map[attackee.first][attackee.second].attackPoint -= map[attacker.first][attacker.second].attackPoint;
        map[attackee.first][attackee.second].lastAttackedTime = globalTime;

        // 공격받는 포탑이 파괴되면 potapNum 감소
        if (map[attackee.first][attackee.second].attackPoint <= 0) {
            potapNum--;
            map[attackee.first][attackee.second].attackPoint = 0;
        }

        // 경로에 있는 포탑 공격
        int currentI = attackee.first;
        int currentJ = attackee.second;

        while (parent[currentI][currentJ].first != -1) // 공격자까지 역추적 (공격자는 제외)
        {
            int prevI = parent[currentI][currentJ].first;
            int prevJ = parent[currentI][currentJ].second;

            if (prevI == attacker.first && prevJ == attacker.second) break; // 공격자 본인은 공격받지 않음

            map[prevI][prevJ].attackPoint -= (map[attacker.first][attacker.second].attackPoint / 2);
            map[prevI][prevJ].lastAttackedTime = globalTime;

            // 경로상의 포탑이 파괴되면 potapNum 감소
            if (map[prevI][prevJ].attackPoint <= 0) {
                potapNum--;
                map[prevI][prevJ].attackPoint = 0;
            }

            currentI = prevI;
            currentJ = prevJ;
        }
        return (true);
    }
    return (false);
}

// 공격 단계
void attack(void)
{
    // 주변 8방향 이동 (대각선 포함)
    int iNum8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int jNum8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    pair<int, int> attackee = chooseAttackee(); // 피격자 선택
    pair<int, int> attacker = chooseAttacker(); // 공격자 선택

    // cout << "\nAttacker: (" << attacker.first << ", " << attacker.second << ") with Attack Point: " 
    //      << map[attacker.first][attacker.second].attackPoint << "\n";
    // cout << "Attackee: (" << attackee.first << ", " << attackee.second << ") with Attack Point: "
    //         << map[attackee.first][attackee.second].attackPoint << "\n";

    // 공격자와 피격자가 동일한 경우 공격하지 않음 (문제 조건에 따라)
    if (attacker.first == attackee.first && attacker.second == attackee.second) {
        return; 
    }

    // 레이저 공격 시도
    if (tryLaserAttack(attacker, attackee) == true) {
        return; // 레이저 공격 성공 시 일반 공격 건너뜀
    }

    // 포탄 공격 (레이저 공격 실패 시)
    map[attackee.first][attackee.second].attackPoint -= map[attacker.first][attacker.second].attackPoint;
    map[attackee.first][attackee.second].lastAttackedTime = globalTime;
    
    // 피격 포탑 파괴 시 potapNum 감소
    if (map[attackee.first][attackee.second].attackPoint <= 0) {
        potapNum--;
        map[attackee.first][attackee.second].attackPoint = 0;
    }

    // 주변 포탑 공격 (공격자는 제외)
    for (int index = 0; index < 8; index++)
    {
        int newI = (attackee.first + iNum8[index] + n) % n; // 맵 경계 처리
        int newJ = (attackee.second + jNum8[index] + m) % m; // 맵 경계 처리

        // 공격자 자신은 공격받지 않음
        if (newI == attacker.first && newJ == attacker.second) continue;

        if (map[newI][newJ].attackPoint > 0) // 공격력이 0보다 큰 포탑만 공격
        {
            map[newI][newJ].attackPoint -= (map[attacker.first][attacker.second].attackPoint / 2);
            map[newI][newJ].lastAttackedTime = globalTime;

            // 주변 포탑 파괴 시 potapNum 감소
            if (map[newI][newJ].attackPoint <= 0) {
                potapNum--;
                map[newI][newJ].attackPoint = 0;
            }
        }
    }
}

// 정비 단계
void fix(void)
{
    // 살아있는 포탑만 대상으로 정비 수행
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // 공격력이 0 이하면 파괴된 포탑이므로 정비 대상에서 제외하고 0으로 유지
            if (map[i][j].attackPoint <= 0)
            {
                map[i][j].attackPoint = 0;
                continue;
            }
            
            // 공격도, 피격도 당하지 않은 포탑은 공격력 1 증가
            // lastAttackTime과 lastAttackedTime이 globalTime과 다를 경우에만 증가
            if (map[i][j].lastAttackedTime != globalTime && map[i][j].lastAttackTime != globalTime)
                map[i][j].attackPoint++;
        }
    }
}

// 최종적으로 가장 강한 포탑의 공격력 출력
void printBiggestAttackPoint(void)
{
    int finalMaxAttackPoint = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j].attackPoint > 0)
                finalMaxAttackPoint = max(finalMaxAttackPoint, map[i][j].attackPoint);
        }
    }
    cout << finalMaxAttackPoint << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    input(); // 초기 맵 입력

    for (int time = 1; time <= k; time++)
    {
        globalTime = time; // 현재 시간 업데이트
        
        // 살아있는 포탑이 1개 이하면 게임 종료
        if (potapNum <= 1)
            break;
        
        attack(); // 공격 단계
        // cout << "After Attack at Time " << time << ":\n";
        // printMap(); // 현재 맵 상태 출력 (디버깅용)

        // 공격 후 살아있는 포탑이 1개 이하면 게임 종료
        if (potapNum <= 1)
            break;

        fix(); // 정비 단계
        // cout << "After Fix at Time " << time << ":\n";
        // printMap(); // 현재 맵 상태 출력 (디버깅용)
    }

    printBiggestAttackPoint(); // 최종 결과 출력

    return 0;
}
