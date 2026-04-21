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

    // dp[i][j][0]: Number of non-crossing spanning trees on the interval [i, j]
    // such that the edge (i, j) is present in the tree.
    // dp[i][j][1]: Number of non-crossing spanning trees on the interval [i, j].
    // In this state, i and j are guaranteed to be connected because it's a spanning tree.
    static int dp[505][505][2];

    for (int i = 1; i <= n; ++i) {
        dp[i][i][1] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            
            // Calculate dp[i][j][0]: trees on [i, j] where (i, j) is an edge.
            // We split the interval at k, where [i, k] and [k+1, j] are two sub-trees
            // that are joined by the edge (i, j).
            if (a[i][j]) {
                long long sum = 0;
                for (int k = i; k < j; ++k) {
                    sum = (sum + (long long)dp[i][k][1] * dp[k + 1][j][1]) % MOD;
                }
                dp[i][j][0] = sum;
            }
            
            // Calculate dp[i][j][1]: all non-crossing spanning trees on [i, j].
            // We pick the "last" edge incident to j, say (k, j).
            // Then [i, k] forms a spanning tree and [k, j] forms a spanning tree
            // where (k, j) is an edge.
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
