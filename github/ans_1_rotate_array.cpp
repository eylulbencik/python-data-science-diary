#include <iostream>
using namespace std;

void reverse_portion(int arr[], int start, int end) {
    // 1. Loop while start < end
    while (start < end) {
        // 2. Swap arr[start] and arr[end]
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        // 3. Move pointers inward
        start++;
        end--;
    }
}

void rotate_array(int arr[], int size, int k) {
    // 4. Handle empty array or k=0
    if (size == 0 || k == 0) {
        return;
    }
    // 5. Normalize k using modulo
    k = k % size;
    // 6. Check if rotation needed after normalization
    if (k == 0) {
        return;
    }
    // 7. Reverse entire array
    reverse_portion(arr, 0, size - 1);
    // 8. Reverse first k elements
    reverse_portion(arr, 0, k - 1);
    // 9. Reverse remaining elements
    reverse_portion(arr, k, size - 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int k = 2;
    // 10. Call rotate_array function
    rotate_array(arr, size, k);
    return 0;
}
