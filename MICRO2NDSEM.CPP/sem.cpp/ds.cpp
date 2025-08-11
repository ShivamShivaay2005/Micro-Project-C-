#include <iostream>
#include <stack>
#include <string>

using namespace std;

class TextEditor {
private:
    stack<string> undoStack;
    stack<string> redoStack;
    string currentText;

public:
    void addText(const string& text) {
        undoStack.push(currentText);
        currentText += text;
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(currentText);
            currentText = undoStack.top();
            undoStack.pop();
        } else {
            cout << "Nothing to undo." << endl;
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(currentText);
            currentText = redoStack.top();
            redoStack.pop();
        } else {
            cout << "Nothing to redo." << endl;
        }
    }

    void display() const {
        cout << "Current Text: \"" << currentText << "\"" << endl;
    }
};

int main() {
    TextEditor editor;
    string command;

    cout << "Simple Text Editor with Undo/Redo Feature" << endl;
    cout << "Commands: add, undo, redo, display, exit" << endl;

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, command);

        if (command == "add") {
            cout << "Enter text to add: ";
            string textToAdd;
            getline(cin, textToAdd);
            editor.addText(textToAdd);
            cout << "Text added." << endl;

        } else if (command == "undo") {
            editor.undo();

        } else if (command == "redo") {
            editor.redo();

        } else if (command == "display") {
            editor.display();

        } else if (command == "exit") {
            cout << "Exiting editor." << endl;
            break;

        } else {
            cout << "Unknown command. Please use: add, undo, redo, display, exit." << endl;
        }
    }

    return 0;
}

