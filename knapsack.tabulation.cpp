#include <bits/stdc++.h>
#include <vector>

using namespace std;

int knapsack(int maxWeight, int weightList[], int profitList[], int size){
    vector<int> dp(maxWeight+1, 0);
    for (int i = 1; i <= size; i++) {
        for (int j = maxWeight; j >= 0 ; j--) {
            if(weightList[i - 1] <= j)
                dp[j] = max(dp[j], dp[j - weightList[i-1]] + profitList[i-1]);
        
        }
    }   return dp[maxWeight];
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
