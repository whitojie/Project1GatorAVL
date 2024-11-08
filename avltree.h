#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iomanip>
using namespace std;

struct Node {
    string name;
    int id;
    Node *left, *right;

    Node(string name, int id) {
        this->name = std::move(name);
        this->id = id;
        this->left = nullptr;
        this->right = nullptr;
    }

};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}


    bool insert(const string& name, int id);
    void inOrder() const;
    void preOrder() const;
    void postOrder() const;
    void searchID(int id);
    void searchName(string name);
    void printLevel();
    bool remove(int id);
    bool removeInorder(int n);
    [[nodiscard]] Node* getRoot() const;
    int height(Node *node) const;

private:
    int getBalance(Node *node) const;
    static Node *rightRotate(Node *current);
    static Node *leftRotate(Node *current);
    Node *balanceTree(Node *current);
    void inOrderHelper(Node* root, vector<Node*> &nodes) const;
    void preOrderHelper(Node* root, vector<Node*> &nodes) const;
    void postOrderHelper(Node* root, vector<Node*> &nodes) const;
    void inOrder(Node *node) const;
    void preOrder(Node *node) const;
    void postOrder(Node *node) const;
    void printLevelCount(Node *root);
    void searchID(Node *node, int id);
    void searchName(Node *node, string name);
    void removeID(Node *&currentNode, int id);
    Node *successor(Node *node);
    bool removeInorder(Node *node, int n);
    bool remove(Node *&node, int id);

    Node *root;
};

int AVLTree::height(Node *node) const {
    if (!node) {
        return 0;
    }
    return max(height(node -> left), height(node -> right)) + 1;
}
void AVLTree::inOrder() const{
    inOrder(root);
}

void AVLTree::preOrder() const{
    preOrder(root);
}

void AVLTree::postOrder() const{
    postOrder(root);
}

void AVLTree::searchID(int id) {
    searchID(root, id);
}

void AVLTree::searchName(string name){
    searchName(root, name);
}
void AVLTree::printLevel() {
    printLevelCount(root);
}

bool AVLTree::remove(int id) {
    return remove(root, id);
}

bool AVLTree::removeInorder(int n) {
    return removeInorder(root, n);
}

void AVLTree::printLevelCount(Node *root) {
    cout << height(root) << endl;
}

void AVLTree::searchID(Node *node, int id){
    vector<Node*> nodes;
    inOrderHelper(root, nodes);
    bool found = false;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] -> id == id) {
            cout << nodes[i]  ->  name << endl;
            found = true;
            break;
        }
    }
    if (!found){
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::searchName(Node *node, string name) {
    for (const char &c : name) {
        if (!isalpha(c) && c != ' ') {
            cout << "unsuccessful" << endl;
            return;
        }
    }
    vector<Node*> nodes;
    preOrderHelper(node, nodes);
    bool found = false;

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] -> name == name) {
            if (nodes[i]  ->  id < 10000000) {
                cout << setfill(' ') << setw(8) << nodes[i] -> id << endl;
            } else {
                cout << nodes[i] -> id << endl;
            }
            found = true;
        }
    }

    if (!found) {
        cout << "unsuccessful" << endl;
    }
}


int AVLTree::getBalance(Node *node) const {
    if (!node) {
        return 0;
    }
    return height(node -> left) - height(node -> right);
}

Node *AVLTree::rightRotate(Node *current) {
    Node *newRoot = current->left;
    Node *temp = newRoot->right;

    newRoot->right = current;
    current->left = temp;

    return newRoot;
}


Node *AVLTree::leftRotate(Node *current) {
    Node *newRoot = current->right;
    Node *temp = newRoot->left;

    newRoot->left = current;
    current->right = temp;

    return newRoot;
}

Node *AVLTree::balanceTree(Node *current) {
    int balanceFactor = getBalance(current);
    if (balanceFactor > 1 && getBalance(current->left) >= 0) {
        return rightRotate(current);
    }
    if (balanceFactor > 1 && getBalance(current->left) < 0) {
        current->left = leftRotate(current->left);
        return rightRotate(current);
    }
    if (balanceFactor < -1 && getBalance(current->right) <= 0) {
        return leftRotate(current);
    }
    if (balanceFactor < -1 && getBalance(current->right) > 0) {
        current->right = rightRotate(current->right);
        return leftRotate(current);
    }
    return current;
}

bool AVLTree::insert(const string& personName, int identifier) {
    for (const char &character : personName) {
        if (!isalpha(character) && character != ' ') {
            return false;
        }
    }

    if (root == nullptr) {
        root = new Node(personName, identifier);
        return true;
    }

    Node *currentNode = root, *parentNode = nullptr;

    while (currentNode != nullptr) {
        parentNode = currentNode;
        if (identifier < currentNode->id) {
            currentNode = currentNode->left;
        } else if (identifier > currentNode->id) {
            currentNode = currentNode->right;
        } else {
            return false;
        }
    }

    Node *newEntry = new Node(personName, identifier);

    if (identifier < parentNode->id) {
        parentNode->left = newEntry;
    } else {
        parentNode->right = newEntry;
    }

    root = balanceTree(root);

    return true;
}


void AVLTree::inOrderHelper(Node* root, vector<Node*> &nodes) const
{
    if (root == nullptr)
        return;
    inOrderHelper(root -> left, nodes);
    nodes.push_back(root);
    inOrderHelper(root -> right, nodes);
}
void AVLTree::preOrderHelper(Node* root, vector<Node*> &nodes) const
{
    if (root == nullptr)
        return;
    nodes.push_back(root);
    preOrderHelper(root -> left, nodes);
    preOrderHelper(root -> right, nodes);
}
void AVLTree::postOrderHelper(Node* root, vector<Node*> &nodes) const
{
    if (root == nullptr)
        return;
    postOrderHelper(root -> left, nodes);
    postOrderHelper(root -> right, nodes);
    nodes.push_back(root);
}

void AVLTree::inOrder(Node *node) const {
    vector<Node*> nodes;
    inOrderHelper(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1)
            cout << nodes[i] -> name << ", ";
        else
            cout << nodes[i] -> name << endl;

    }
}
void AVLTree::preOrder(Node *node) const {
    vector<Node*> nodes;
    preOrderHelper(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1)
            cout << nodes[i] -> name << ", ";
        else
            cout << nodes[i] -> name <<endl;

    }
}
void AVLTree::postOrder(Node *node) const {
    vector<Node*> nodes;
    postOrderHelper(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1)
            cout << nodes[i] -> name << ", ";
        else
            cout << nodes[i] -> name << endl;

    }
}

Node *AVLTree::successor(Node *node) {
    Node *current = node;
    while (current -> left != nullptr) {
        current = current -> left;
    }
    return current;
}

void AVLTree::removeID(Node *&currentNode, int id) {
    if (currentNode == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }

    if (id < currentNode->id) {
        removeID(currentNode->left, id);
    } else if (id > currentNode->id) {
        removeID(currentNode->right, id);
    } else {
        cout << "successful" << endl;
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            delete currentNode;
            currentNode = nullptr;
        } else if (currentNode->left == nullptr) {
            Node *tempNode = currentNode;
            currentNode = currentNode->right;
            delete tempNode;
        } else if (currentNode->right == nullptr) {
            Node *tempNode = currentNode;
            currentNode = currentNode->left;
            delete tempNode;
        } else {
            Node *successorNode = successor(currentNode->right);
            currentNode->id = successorNode->id;
            currentNode->name = successorNode->name;
            removeID(currentNode->right, successorNode->id);
        }
    }
}

bool AVLTree::remove(Node *&currentNode, int id) {
    if (currentNode == nullptr) {
        return false;
    }

    if (id < currentNode->id) {
        return remove(currentNode->left, id);
    } else if (id > currentNode->id) {
        return remove(currentNode->right, id);
    } else {
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            delete currentNode;
            currentNode = nullptr;
        } else if (currentNode->left == nullptr) {
            Node *tempNode = currentNode;
            currentNode = currentNode->right;
            delete tempNode;
        } else if (currentNode->right == nullptr) {
            Node *tempNode = currentNode;
            currentNode = currentNode->left;
            delete tempNode;
        } else {
            Node *tempNode = currentNode->right;
            while (tempNode->left != nullptr) {
                tempNode = tempNode->left;
            }
            currentNode->id = tempNode->id;
            currentNode->name = tempNode->name;
            return remove(currentNode->right, tempNode->id);
        }
        return true;
    }
}


bool AVLTree::removeInorder(Node *node, int n) {
    if(!node){
        return false;
    }

    vector<Node*> nodes;
    inOrderHelper(node, nodes);
    if(n > nodes.size() - 1){
        return false;
    }
    else{
        return remove(nodes[n] -> id);
    }
}

Node* AVLTree::getRoot() const {
    return root;
}

