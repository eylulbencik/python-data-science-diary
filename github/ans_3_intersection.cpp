#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

int find_intersection(int arr1[], int size1, int arr2[], int size2, int result[]) {
    // 1. Handle empty arrays
    if (size1 == 0 || size2 == 0) {
        return 0;
    }
    // 2. Initialize three pointers (i, j, k)
    int i = 0, j = 0, k = 0;
    // 3. Loop while both pointers valid
    while (i < size1 && j < size2) {
        // 4. Compare elements at current pointers
        if (arr1[i] < arr2[j]) {
            i++;
        } else if (arr1[i] > arr2[j]) {
            j++;
        } else {
            // 5. Check for duplicate in result
            if (k == 0 || result[k - 1] != arr1[i]) {
                // 6. Add to result if not duplicate
                result[k++] = arr1[i];
            }
            // 7. Move both pointers forward
            i++;
            j++;
        }
    }
    return k;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {3, 4, 5, 6, 7};
    int size1 = 5;
    int size2 = 5;
    int result[MAX_SIZE];
    // 8. Call find_intersection and get result size
    int result_size = find_intersection(arr1, size1, arr2, size2, result);
    return 0;
}
