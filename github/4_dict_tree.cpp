#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct DictNode {
    string word;
    string meaning;
    DictNode* left;
    DictNode* right;
};

DictNode* createNode(string w, string m) {
    DictNode* newNode = new DictNode;
    newNode->word = w;
    newNode->meaning = m;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

string toLower(string str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

DictNode* insert(DictNode* root, string word, string meaning) {
    if (root == NULL) {
        return createNode(word, meaning);
    }
    
    string wordLower = toLower(word);
    string rootWordLower = toLower(root->word);
    
    if (wordLower == rootWordLower) {
        root->meaning = meaning;
        return root;
    }
    
    if (wordLower < rootWordLower) {
        root->left = insert(root->left, word, meaning);
    } else {
        root->right = insert(root->right, word, meaning);
    }
    return root;
}

DictNode* search(DictNode* root, string word) {
    if (root == NULL) return NULL;
    
    string wordLower = toLower(word);
    string rootWordLower = toLower(root->word);
    
    if (wordLower == rootWordLower) return root;
    if (wordLower < rootWordLower) return search(root->left, word);
    return search(root->right, word);
}

DictNode* findMin(DictNode* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

DictNode* deleteWord(DictNode* root, string word) {
    if (root == NULL) return root;
    
    string wordLower = toLower(word);
    string rootWordLower = toLower(root->word);
    
    if (wordLower < rootWordLower) {
        root->left = deleteWord(root->left, word);
    } 
    else if (wordLower > rootWordLower) {
        root->right = deleteWord(root->right, word);
    } 
    else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        else if (root->left == NULL) {
            DictNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            DictNode* temp = root->left;
            delete root;
            return temp;
        }
        else {
            DictNode* successor = findMin(root->right);
            root->word = successor->word;
            root->meaning = successor->meaning;
            root->right = deleteWord(root->right, successor->word);
        }
    }
    return root;
}

void displayAlphabetically(DictNode* root) {
    if (root == NULL) return;
    displayAlphabetically(root->left);
    cout << root->word << " - " << root->meaning << endl;
    displayAlphabetically(root->right);
}

void printTree(DictNode* root, int space = 0) {
    if (root == NULL) return;
    space += 4;
    printTree(root->right, space);
    cout << endl;
    for (int i = 4; i < space; i++) cout << " ";
    cout << root->word << endl;
    printTree(root->left, space);
}

int countWords(DictNode* root) {
    if (root == NULL) return 0;
    return 1 + countWords(root->left) + countWords(root->right);
}

void findWordsWithPrefix(DictNode* root, string prefix) {
    if (root == NULL) return;
    
    string prefixLower = toLower(prefix);
    string wordLower = toLower(root->word);
    
    if (wordLower.substr(0, prefix.length()) == prefixLower) {
    
        cout << "  " << root->word << " - " << root->meaning << endl;
    }
    
    findWordsWithPrefix(root->left, prefix);
    findWordsWithPrefix(root->right, prefix);
}

int main() {
    DictNode* dict = NULL;
    
    // Insert in balanced order (middle-first approach) to avoid deep tree
    // Middle element first
    dict = insert(dict, "integer", "Whole number without decimal");
    
    // Left subtree elements
    dict = insert(dict, "data", "Information stored in computer");
    dict = insert(dict, "binary", "Number system with base 2");
    dict = insert(dict, "algorithm", "Step-by-step problem solving procedure");
    dict = insert(dict, "compiler", "Translates source code to machine code");
    dict = insert(dict, "hash", "Maps data to fixed-size values");
    dict = insert(dict, "function", "Reusable block of code");
    dict = insert(dict, "graph", "Data structure with nodes and edges");
    
    // Right subtree elements
    dict = insert(dict, "queue", "FIFO data structure");
    dict = insert(dict, "loop", "Control structure that repeats code");
    dict = insert(dict, "pointer", "Variable storing memory address");
    dict = insert(dict, "tree", "Hierarchical data structure");
    dict = insert(dict, "stack", "LIFO data structure");
    dict = insert(dict, "variable", "Named storage location");
    
    cout << "Dictionary Tree Structure:" << endl;
    printTree(dict);
    
    cout << "\n\nTotal words: " << countWords(dict) << endl;
    
    cout << "\n\nAll Words (Alphabetically):" << endl;
    displayAlphabetically(dict);
    
    cout << "\n\nSearch Examples:" << endl;
    string searches[] = {"tree", "stack", "python"};
    for (int i = 0; i < 3; i++) {
        DictNode* result = search(dict, searches[i]);
        if (result != NULL) {
            cout << searches[i] << ": " << result->meaning << endl;
        } else {
            cout << searches[i] << ": Not found" << endl;
        }
    }
    
    cout << "\n\nWords starting with 'al':" << endl;
    findWordsWithPrefix(dict, "al");
    
    cout << "\nWords starting with 'co':" << endl;
    findWordsWithPrefix(dict, "co");
    
    cout << "\n\nDeleting 'binary'..." << endl;
    dict = deleteWord(dict, "binary");
    
    cout << "\nAfter deletion (" << countWords(dict) << " words):" << endl;
    displayAlphabetically(dict);
    
    return 0;
}
