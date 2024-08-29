#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int minMult(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len < n; len++) {  
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;

            for (int k = i + 1; k < j; k++) {
                int cost = dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    unsigned size, element;
    cout << "Enter the number of elements: " && cin >> size;
    vector<int> vec;
    for(int i = 0; i < size; i++){
        cout << "Enter value of element" << i+1 << ": " && cin >> element;
        vec.push_back(element);
    }
    cout << "Minimum multiplication cost: " << minMult(vec) << endl;
    return 0;
}
