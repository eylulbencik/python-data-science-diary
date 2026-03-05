#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solution(int A) {
    char s[20];
    sprintf(s, "%d", A);
    int n = strlen(s);

    char *out = malloc(n + 1);
    int left = 0, right = n - 1, p = 0;
    int turn = 0;

    while (left <= right) {
        if (turn == 0) out[p++] = s[left++];
        else out[p++] = s[right--];
        turn = 1 - turn;
    }

    out[p] = '\0';
    int result = atoi(out);
    free(out);
    return result;
}

int main() {
    int a;
    printf("Enter A: ");
    scanf("%d", &a);
    printf("%d\n", solution(a));
    return 0;
}
