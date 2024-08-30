#include <bits/stdc++.h>

using namespace std;

int knapsack(int maxWeight, int weightList[], int profitList[], int size){
    if (size == 0 || maxWeight == 0) return 0;
    if (weightList[size-1] > maxWeight) return knapsack(maxWeight, weightList, profitList, size-1);
    else{
        return max(knapsack(maxWeight, weightList, profitList, size-1), profitList[size-1] + knapsack(maxWeight - weightList[size-1], weightList, profitList, size-1));
    };
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
