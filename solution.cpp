#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    // dp[i][j][0]: i and j are connected by an edge, and they form a spanning tree on i...j
    // dp[i][j][1]: i and j are connected by a path, and they form a spanning tree on i...j
    static long long dp[505][505][2];

    for (int i = 1; i <= n; ++i) {
        dp[i][i][1] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            
            // Calculate dp[i][j][0]
            if (a[i][j]) {
                long long sum = 0;
                for (int k = i; k < j; ++k) {
                    sum = (sum + (long long)dp[i][k][1] * dp[k + 1][j][1]) % MOD;
                }
                dp[i][j][0] = sum;
            }
            
            // Calculate dp[i][j][1]
            long long sum = 0;
            for (int k = i; k < j; ++k) {
                sum = (sum + (long long)dp[i][k][1] * dp[k][j][0]) % MOD;
            }
            dp[i][j][1] = sum;
        }
    }

    cout << dp[1][n][1] << endl;

    return 0;
}
