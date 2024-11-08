#include <iostream>
#include <string>
#include <vector>
#include "avltree.h"
using namespace std;

void run(string cmd, AVLTree &tree) {
    int index = cmd.find(' ');
    string call = cmd.substr(0, index);
    cmd = cmd.substr(index + 1);
    if (call.compare("insert") == 0) {
        cmd.erase(0, 1);
        index = cmd.find('\"');
        string name = cmd.substr(0, index);
        cmd.erase(0, index + 2);

        bool validId = (cmd.length() >= 8) && (stoi(cmd) < 100000000);
        if (validId) {
            int id = stoi(cmd);
            bool insertionSuccess = tree.insert(name, id);
            cout << (insertionSuccess ? "successful" : "unsuccessful") << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    } else if (call == "remove") {
        bool validId = (cmd.length() >= 8) && (stoi(cmd) < 100000000);
        if (validId) {
            bool removalSuccess = tree.remove(stoi(cmd));
            cout << (removalSuccess ? "successful" : "unsuccessful") << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    } else if (call == "removeInorder") {
        bool removalInorderSuccess = tree.removeInorder(stoi(cmd));
        cout << (removalInorderSuccess ? "successful" : "unsuccessful") << endl;
    } else if (call == "search") {
        if (cmd.front() == '\"') {
            string name = cmd.substr(1, cmd.length() - 2);
            tree.searchName(name);
        } else {
            bool validId = (cmd.length() >= 8) && (stoi(cmd) < 100000000);
            if (validId) {
                tree.searchID(stoi(cmd));
            }
        }

    } else if (call == "printInorder") {
        tree.inOrder();
    } else if (call == "printPreorder") {
        tree.preOrder();
    } else if (call == "printPostorder") {
        tree.postOrder();
    } else if (call == "printLevelCount") {
        tree.printLevel();
    }
}



int main() {
    AVLTree avltree;
    int lines;
    cin >> lines;
    string line;
    vector<string> commands;

    for (int i = 0; i < lines + 1; i++)
    {
        getline(cin, line);
        commands.push_back(line);
    }
    for (int i = 0; i < commands.size(); i++){
        run(commands[i], avltree);
    }

    return 0;
}
