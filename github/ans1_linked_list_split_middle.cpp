#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertEnd(Node*& head, int value);

void findMiddleAndSplit(Node* head, Node*& firstHalf, Node*& secondHalf) {
    // 1. Check for empty list
    if (!head) {
        firstHalf = nullptr;
        secondHalf = nullptr;
        return;
    }
    
    // 2. If only one element
    if (!head->next) {
        firstHalf = head;
        secondHalf = nullptr;
        return;
    }
    
    // 3. Initialize slow and fast pointers
    Node* slow = head;
    Node* fast = head;
    Node* prev = nullptr;
    
    // 4. Move slow by 1 and fast by 2 until fast reaches the end
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // 5. Split the list into two halves
    firstHalf = head;
    secondHalf = slow;
    
    // 6. Add null to end first half
    if (prev)
        prev->next = nullptr;
}

int main() {
    Node* head = nullptr;
    
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);
    insertEnd(head, 6);
    
    Node* firstHalf = nullptr;
    Node* secondHalf = nullptr;
    
    findMiddleAndSplit(head, firstHalf, secondHalf);
    
    return 0;
}
