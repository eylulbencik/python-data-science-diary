#include <stdio.h>
#include <time.h>

int max(int x, int y)
{
    return (x > y) ? x : y;
}

int knapsack_recursive(int W, int wt[], int val[], int n)
{
    if (n == 0 || W == 0){
        return 0;
    }
    if (wt[n - 1] > W){
        return knapsack_recursive(W, wt, val, n - 1);
    }
    else{
        int take = val[n - 1] + knapsack_recursive(W - wt[n - 1], wt, val, n - 1);
        int skip = knapsack_recursive(W, wt, val, n - 1);
        return max(take, skip);
    }
}

int knapsack_dp(int W, int wt[], int val[], int n)
{
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++){
        for (int w = 0; w <= W; w++){
            if (i == 0 || w == 0){
                dp[i][w] = 0;
            }
            else if (wt[i - 1] <= w){
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]],
                               dp[i - 1][w]);
            }else{
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main(){
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;

    int n = sizeof(val) / sizeof(val[0]);

    clock_t start, end;

    start = clock();
    int rec_result = knapsack_recursive(W, wt, val, n);
    end = clock();
    double rec_time = (double)(end - start) / 1000;

    start = clock();
    int dp_result = knapsack_dp(W, wt, val, n);
    end = clock();
    double dp_time = (double)(end - start) / 1000;

    printf("Recursive result: %d\n", rec_result);
    printf("Recursive time: %f seconds\n", rec_time);

    printf("DP result: %d\n", dp_result);
    printf("DP time: %f seconds\n", dp_time);
    return 0;
}
