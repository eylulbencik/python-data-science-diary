#include <stdio.h>
#include <stdbool.h>
#define N 6

int main() {
    int g[N][N] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0}
    };

    int d[N];
    bool flg[N];
    int i, k;

    for (i = 0; i < N; i++) {
        d[i] = 0;
        flg[i] = false;
    }

    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            if (g[i][k] == 1) {
                d[k]++;
            }
        }
    }
    printf("Topological Sort: ");

    for (i = 0; i < N; i++) {
        int temp = -1;

        for (k = 0; k < N; k++) {
            if (!flg[k] && d[k] == 0) {
                temp = k;
                break;
            }
        }
        if (temp == -1) {
            printf("\nError: Cycle detected!\n");
            return 1;
        }
        flg[temp] = true;
        printf("%d ", temp);

        for (int m = 0; m < N; m++) {
            if (g[temp][m] == 1) {
                d[m]--;
            }
        }
    }
    printf("\n");
    return 0;
}