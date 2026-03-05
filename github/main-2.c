#include <stdio.h>

int main() {
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500};
    int size = sizeof(coins) / sizeof(coins[0]);
    int remaining = 93;

    int solution[100];
    int solIndex = 0;

    printf("Greedy Coin Changing for %d:\n", remaining);

    for (int i = size - 1; i >= 0; i--) {
        while (remaining >= coins[i]) {
            remaining -= coins[i];
            solution[solIndex++] = coins[i];
        }
    }

    printf("Coins used: ");
    for (int i = 0; i < solIndex; i++) {
        printf("%d ", solution[i]);
    }
    printf("\nTotal coins: %d\n", solIndex);

    return 0;
}
