#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;
int grid[1005][1005];
int dist2[1005][1005];
int dist3[1005][1005];
int n, m;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void bfs(int start_r, int start_c, int dist[1005][1005]) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = INF;
        }
    }
    queue<pair<int, int>> q;
    q.push({start_r, start_c});
    dist[start_r][start_c] = 0;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != 1) {
                if (dist[nr][nc] == INF) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    int start_r = -1, start_c = -1;
    int end_r = -1, end_c = -1;
    vector<pair<int, int>> shops;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start_r = i;
                start_c = j;
            } else if (grid[i][j] == 3) {
                end_r = i;
                end_c = j;
            } else if (grid[i][j] == 4) {
                shops.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dist2[i][j] = INF;
            dist3[i][j] = INF;
        }
    }

    if (start_r != -1 && start_c != -1) {
        bfs(start_r, start_c, dist2);
    }
    if (end_r != -1 && end_c != -1) {
        bfs(end_r, end_c, dist3);
    }

    int ans = INF;
    for (auto shop : shops) {
        int r = shop.first;
        int c = shop.second;
        if (dist2[r][c] != INF && dist3[r][c] != INF) {
            ans = min(ans, dist2[r][c] + dist3[r][c]);
        }
    }

    if (ans == INF) {
        cout << 0 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
