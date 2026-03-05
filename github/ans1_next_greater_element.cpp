#include <iostream>
#include <stack>
using namespace std;

void nextGreaterElement(int arr[], int n, int result[]) {
    // 1. Define stack
    stack<int> s;
    
    // 2. Initialize result array with -1
    for (int i = 0; i < n; i++) {
        result[i] = -1;
    }
    
    // 3. Traverse array from right to left
    for (int i = n - 1; i >= 0; i--) {
        // 4. Pop smaller or equal elements from stack
        while (!s.empty() && arr[s.top()] <= arr[i]) {
            // 5. Pop operation 
            s.pop();
        }
        
        // 6. If stack not empty, find next greater element
        if (!s.empty()) {
            // 7. Assign value to result array
            result[i] = arr[s.top()];
        }
        
        // 8. Push current index to stack
        s.push(i);
    }
}

void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    int arr[] = {4, 5, 2, 25};
    int n = 4;
    int result[4];
    
    cout << "Input:  ";
    printArray(arr, n);
    cout << endl;
    
    nextGreaterElement(arr, n, result);
    cout << "Output: ";
    printArray(result, n);
    cout << endl;
    
    return 0;
}
