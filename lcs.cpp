#include <bits/stdc++.h>
using namespace std;

int lcs(string &S1, string &S2) {
    int m = S1.size();
    int n = S2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (S1[i - 1] == S2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m][n];
}

int main() {
    string S1, S2;
    cout << "Enter first string: " && cin >> S1;
    cout << "Enter second string: " && cin >> S2;
    cout << "Length of LCS is " << lcs(S1, S2) << endl;
    return 0;
}

