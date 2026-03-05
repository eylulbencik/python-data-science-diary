#include <stdio.h>

int LEFT(int i) { return 2 * i; }
int RIGHT(int i) { return 2 * i + 1; }

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void MAX_HEAPIFY(int A[], int i, int n) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;

    if (l <= n && A[l] > A[i])
        largest = l;
    else
        largest = i;

    if (r <= n && A[r] > A[largest])
        largest = r;

    if (largest != i) {
        swap(&A[i], &A[largest]);
        MAX_HEAPIFY(A, largest, n);
    }
}

void printArray(int A[], int n) {
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {0, 3, 9, 2, 1, 4, 5, 7};
    int n = 7;

    printf("Before heapify:\n");
    printArray(A, n);

    MAX_HEAPIFY(A, 1, n);

    printf("After heapify:\n");
    printArray(A, n);

    return 0;
}
