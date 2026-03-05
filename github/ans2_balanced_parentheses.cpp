#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(string str) {
    // 1. Define stack
    stack<char> s;
    
    // 2. Loop through string
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        
        // 3. Check opening brackets
        if (ch == '(' || ch == '{' || ch == '[') {
            // 4. Push opening brackets to stack
            s.push(ch);
        }
        // 5. Check closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            // 6. Check if stack is empty
            if (s.empty()) {
                return false;
            }
            
            // 7. Get top element from stack
            char top = s.top();
            s.pop();
            
            // 8. Check if brackets match
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    // 9. Check if stack is empty at the end
    return s.empty();
}

int main() {
    string test = "{[()]}";
    
    cout << "Input: \"" << test << "\"" << endl;
    cout << "Output: " << (isBalanced(test) ? "Balanced" : "Not Balanced") << endl;
    
    return 0;
}
