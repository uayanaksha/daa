#include <bits/stdc++.h>
#include <vector>

using namespace std;

int knapsack_r(int maxWeight, int weightList[], int profitList[], int idx, vector<vector<int>> &dp){
    if (idx < 0) return 0;
    if (dp[idx][maxWeight] != -1) {
        return dp[idx][maxWeight];
    }
    if(weightList[idx] > maxWeight){
        dp[idx][maxWeight] = knapsack_r(maxWeight, weightList, profitList, idx-1, dp);
    }   else {
        dp[idx][maxWeight] = max(profitList[idx] + knapsack_r(maxWeight - weightList[idx], weightList, profitList, idx-1, dp), knapsack_r(maxWeight, weightList, profitList, idx-1, dp));
    }
        return dp[idx][maxWeight];

}

int knapsack(int maxWeight, int weightList[], int profitList[], int size){
    vector<vector<int>> dp(size, vector<int>(maxWeight+1, -1));
    return knapsack_r(maxWeight, weightList, profitList, size-1, dp);
}

int main(void){
    int profitList[] = {60, 100, 120, 150, 110};
    int weightList[] = {10, 20, 30, 40, 60};
    int maxWeight = 60;
    int size = sizeof(profitList)/sizeof(profitList[0]);
    int output = knapsack(maxWeight, weightList, profitList, size);
    cout << "Maximum profit: " <<  output << endl;
    return 0;
}
