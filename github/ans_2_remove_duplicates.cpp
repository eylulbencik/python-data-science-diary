#include <iostream>
using namespace std;

int remove_duplicates(int arr[], int size) {
    // 1. Handle base cases (size 0 or 1)
    if (size == 0 || size == 1) {
        return size;
    }
    // 2. Initialize unique position tracker
    int unique_pos = 0;
    // 3. Loop through array starting from index 1
    for (int i = 1; i < size; i++) {
        // 4. Compare current with unique position element
        if (arr[i] != arr[unique_pos]) {
            // 5. Move unique position forward
            unique_pos++;
            // 6. Copy current element to unique position
            arr[unique_pos] = arr[i];
        }
    }
    // 7. Return new size
    return unique_pos + 1;
}

bool is_sorted(int arr[], int size) {
    // 8. Loop through array pairs
    for (int i = 0; i < size - 1; i++) {
        // 9. Check if any element greater than next
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 1, 2, 2, 3, 4, 4, 5};
    int size = 8;
    if (is_sorted(arr, size)) {
        // 10. Call remove_duplicates and get new size
        int new_size = remove_duplicates(arr, size);
    }
    return 0;
}
