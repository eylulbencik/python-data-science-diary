#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Command{
    string type ;
    string text ;
    string oldText;
    int counter=0;
    int pos=0;

};

class TextEditor{

    string text;
    stack<Command> undoStack,redoStack;

public:

    TextEditor() {
        text = "";
    }

    void ins(int pos, const string& newText){
        if(pos < 0|| pos > (int)text.length()){
            cout << "Invalid position !";
            return;
        }
        text.insert(pos,newText);

        Command operation;
        operation.type = "insert";
        operation.text = newText;
        operation.pos = pos;
        undoStack.push(operation); //operation recorded.

        while(!redoStack.empty()){
            redoStack.pop();
        }
        cout << "Inserted \"" << newText << "\" at position " << pos << endl;
    }

    void del(int pos, int count){
        if(pos < 0 || pos >= text.length()){
            cout << "Invalid position!";
            return;
        }

        int realCount = count;
        if(pos + count > text.length()){
            realCount = (int) text.length() - pos ;
        }

        string toDelete = text.substr(pos,realCount);
        text.erase(pos,realCount);

        Command operation;
        operation.type = "delete";
        operation.text = toDelete;
        operation.pos=pos;
        operation.counter=realCount;
        undoStack.push(operation);

        while(!redoStack.empty()){
            redoStack.pop();
        }
        cout << "Deleted " << realCount << " characters(s) from position "<< pos << endl;
    }

    void rep(int pos, int count, const string& newText){
        if(pos < 0 || pos >= text.length()){
            cout << "Invalid position !";
            return;
        }

        int realCount =count;
        if(pos + count > text.length()){
            realCount = (int) text.length() - pos ;
        }

        string oldText = text.substr(pos, realCount);
        text.erase(pos,realCount);
        text.insert(pos,newText);

        Command operation;
        operation.type = "replace";
        operation.text = oldText;
        operation.pos = pos;
        operation.oldText = oldText;

        undoStack.push(operation);

        while(!redoStack.empty()){
            redoStack.pop();
        }
        cout << "Replaced \"" << oldText << "\" with \"" << newText << "\"" << endl;
    }

    void undo(){
        if(undoStack.empty()){
            cout<< "Nothing to undo"<<endl;
            return;
        }

        Command operation = undoStack.top();
        undoStack.pop();

        if(operation.type == "insert"){
            text.erase(operation.pos,operation.text.length());
            cout << "Undo: insert" << endl;
        }else if(operation.type == "delete"){
            text.insert(operation.pos,operation.text);
            cout << "Undo: delete" << endl;
        }
        else if(operation.type == "replace"){
            text.erase(operation.pos,text.length());
            text.insert(operation.pos,operation.text);
            cout<< "Undo: replace" << endl;
        }
        redoStack.push(operation);
    }

    void redo(){
        if(redoStack.empty()){
            cout << "Nothing to redo"<< endl;
            return;
        }

        Command operation = redoStack.top();
        redoStack.pop();

        if(operation.type == "insert"){
            text.insert(operation.pos,operation.text);
            cout << "Redo: insert"<< endl;
        }else if(operation.type == "delete"){
            text.erase(operation.pos,operation.counter);
            cout << "Redo: delete" << endl;
        }else if(operation.type == "replace"){
            text.erase(operation.pos,operation.text.length());
            text.insert(operation.pos,operation.text);
            cout << "Redo: replace" << endl;
        }
        undoStack.push(operation);
    }

    void print(){
        if(text.empty()){
            cout << "[Empty document]" << endl;
        }else{
            cout << "Text: " << text << endl;
        }
    }

    void help(){
        cout << "TEXT EDITOR COMMANDS" << "\n\n";
        cout << "insert <position> <text>  : Insert text at specific position. " << endl;
        cout << "delete <position> <count>  : Delete count characters starting from position." << endl;
        cout << "replace <position> <count> <text>  : Replace count characters with new text " << endl;
        cout << "undo:  Undo the last operation " << endl;
        cout << "redo:  Redo the last undone operation " << endl;
        cout << "print: Display the current text " << endl;
        cout << "help:  Show available commands " << endl;
        cout << "quit:  Exit the editor\n" << endl;

    }
};

int main() {
    TextEditor edi;
    string cmd;

    while (true) {
        cout << "> ";
        cin >> cmd;

        if (cmd == "insert") {
            int p; //integer pos
            if (!(cin >> p)) {
                cout << "Invalid position" << endl;

                cin.clear();
                string garbage;
                cin >> garbage;

                continue;
            }
            if (p < 0) {
                cout << "Invalid position" << endl;
                string garbage;
                getline(cin, garbage);
                continue;
            }
            string s;
            char space; cin.get(space);
            getline(cin, s);

            edi.ins(p, s);
        }
        else if (cmd == "delete") {
            int p, c;

            if (!(cin >> p >> c)) {
                cout << "Invalid position" << endl;
                string garbage;
                cin.clear();
                cin >> garbage;
                continue;
            }
            if (p < 0) {
                cout << "Invalid position" << endl;
                continue;
            }
            edi.del(p, c);
        }
        else if (cmd == "replace") {
            int p, c;

            if (!(cin >> p >> c)) {

                cout << "Invalid position" << endl;

                cin.clear();
                string garbage;
                cin >> garbage;
                continue;
            }

            if (p < 0) {
                cout << "Invalid position" << endl;
                string garbage;
                getline(cin, garbage);
                continue;
            }
            char space;
            cin.get(space);
            string s;
            getline(cin, s);

            edi.rep(p, c, s);
        }
        else if (cmd == "undo") {
            edi.undo();
        }
        else if (cmd == "redo") {
            edi.redo();
        }
        else if (cmd == "print") {
            edi.print();
        }
        else if (cmd == "help") {
            edi.help();
        }
        else if (cmd == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout <<"Unknown command. Type 'help' for available commands." << endl;
        }
    }
    return 0;
}