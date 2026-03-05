#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void swapNodesAtPositions(Node*& head, int m, int n) {
    // 1. Check for invalid positions or same position
    if (m == n || !head)
        return;
    
    // 2. Ensure m < n for simplicity
    if (m > n) {
        int temp = m;
        m = n;
        n = temp;
    }
    
    // 3. Find nodes at positions m and n with their previous nodes
    Node* prevM = nullptr;
    Node* currM = head;
    for (int i = 0; i < m && currM; i++) {
        prevM = currM;
        currM = currM->next;
    }
    
    Node* prevN = nullptr;
    Node* currN = head;
    for (int i = 0; i < n && currN; i++) {
        prevN = currN;
        currN = currN->next;
    }
    
    // 4. Check if both positions exist
    if (!currM || !currN)
        return;
    
    // 5. Update previous nodes' next pointers
    if (prevM)
        prevM->next = currN;
    else
        head = currN;
    
    if (prevN)
        prevN->next = currM;
    
    // 6. Swap next pointers of currM and currN
    Node* temp = currM->next;
    currM->next = currN->next;
    currN->next = temp;
    
    // 7. Handle special case: adjacent nodes
    if (prevM && prevM->next == currM)
        currN->next = currM;
}

int main() {
    // Test data - assume list is already created
    // Example: 1 -> 2 -> 3 -> 4 -> 5
    // Swap positions 1 and 3: 1 -> 4 -> 3 -> 2 -> 5
    Node* head = nullptr;
    
    swapNodesAtPositions(head, 1, 3);
    
    return 0;
}
