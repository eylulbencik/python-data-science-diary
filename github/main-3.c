#include <stdio.h>

#define V 4
#define INF 99999

int min(int a, int b) {
    return a < b ? a : b;
}

void floyd(int W[V][V]) {
    int D[V][V];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            D[i][j] = W[i][j];

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (D[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", D[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int W[V][V] = {
        {0,   3,   INF, 5},
        {2,   0,   INF, 4},
        {INF, 1,   0,   INF},
        {INF, INF, 2,   0}
    };

    floyd(W);

    return 0;
}
