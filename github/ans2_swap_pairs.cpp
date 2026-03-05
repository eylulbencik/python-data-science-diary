#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};
void insertEnd(Node*& head, int value);

void swapPairs(Node*& head) {
    // 1. Check for empty or single node list
    if (!head || !head->next)
        return;
    
    // 2. Create dummy node to simplify head swapping
    Node dummy;
    dummy.next = head;
    Node* prev = &dummy;
    
    // 3. Process pairs
    while (prev->next && prev->next->next) {
        // 4. Identify the two nodes to swap
        Node* first = prev->next;
        Node* second = prev->next->next;
        
        // 5. Perform the swap
        first->next = second->next;
        second->next = first;
        prev->next = second;
        
        // 6. Move prev to next pair
        prev = first;
    }
    
    // 7. Update head
    head = dummy.next;
}

int main() {
    Node* head1 = nullptr;
    
    insertEnd(head1, 1);
    insertEnd(head1, 2);
    insertEnd(head1, 3);
    insertEnd(head1, 4);
    insertEnd(head1, 5);
    insertEnd(head1, 6);
    
    swapPairs(head1);
    
    return 0;
}
