#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct POS {
        int y, x;
};

int main() {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> maze(N, vector<int>(M));
        vector<vector<bool>> visited(N, vector<bool>(M, false));
        string line;

        for (int i = 0; i < N; ++i) {
                cin >> line;
                for (int j = 0; j < M; ++j) {
                        maze[i][j] = line[j] - '0';
                }
        }

        queue<POS> q;
        q.push({ 0, 0 });  // ���� ��ġ
        visited[0][0] = true;
        int steps = 1;  // ���� ��ġ�� �����ϱ� ������ 1���� ����

        // ���� �̵�: ��, ��, ��, ��
        int dx[4] = { 1, -1, 0, 0 };
        int dy[4] = { 0, 0, 1, -1 };

        while (!q.empty()) {
                int size = q.size();
                for (int i = 0; i < size; ++i) {
                        POS cur = q.front();
                        q.pop();

                        if (cur.y == N - 1 && cur.x == M - 1) {  // ���� ������ ����
                                cout << steps;
                                return 0;
                        }

                        for (int j = 0; j < 4; ++j) {
                                int nx = cur.x + dx[j];
                                int ny = cur.y + dy[j];

                                // ���� üũ �� �湮 üũ
                                if (nx >= 0 && nx < M && ny >= 0 && ny < N && maze[ny][nx] == 1 && !visited[ny][nx]) {
                                        visited[ny][nx] = true;
                                        q.push({ ny, nx });
                                }
                        }
                }
                ++steps;  // ���� �Ÿ��� �̵�
        }
}