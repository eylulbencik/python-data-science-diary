#include <iostream>
#include <stack>
using namespace std;

void calculateSpan(int price[], int n, int span[]) {
    // 1. Define stack to store indices
    stack<int> s;
    
    // 2. First element span is always 1
    span[0] = 1;
    s.push(0);
    
    // 3. Loop through remaining elements
    for (int i = 1; i < n; i++) {
        // 4. Pop elements while price is greater
        while (!s.empty() && price[s.top()] <= price[i]) {
            s.pop();
        }
        
        // 5. Calculate span
        if (s.empty()) {
            // 6. If stack empty, span is i+1
            span[i] = i + 1;
        } else {
            // 7. Otherwise span is i minus top index
            span[i] = i - s.top();
        }
        
        // 8. Push current index
        s.push(i);
    }
}

void printArray(int arr[], int n);

int main() {
    int price[] = {100, 80, 60, 70, 60, 75, 85};
    int n = 7;
    int span[7];
    
    cout << "Prices: ";
    printArray(price, n);
    cout << endl;
    
    calculateSpan(price, n, span);
    cout << "Span:   ";
    printArray(span, n);
    cout << endl;
    
    return 0;
}
