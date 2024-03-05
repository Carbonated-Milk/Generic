#pragma once
#include <stack>
using std::stack;

template<class T>
class BST {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;

        Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    Node* root;
    int tSize;

    BST() {
        // implement the contructor here
        root = nullptr;
        tSize = 0;
    }

    ~BST() {
        // implement the destructor here
        clear();
    }

    const Node* getRootNode() const {
        // implement getRootNode here
        // return a pointer to the tree's root node
        return root;
    }

    void insertHelper(Node* node, T item){
        if(item < node->value){
            if (node->left != nullptr){
                insertHelper(node->left, item);
                return;
            }
            node->left = new Node(item);
        }
        else { //item will be greater
            if (node->right != nullptr){
                insertHelper(node->right, item);
                return;
            }
            node->right = new Node(item);
        }
    }

    bool insert(T item) {
        // implement insert here
        // return true if item was inserted, false if item was already in the tree
        if(contains(item)){return false;}
        tSize++;
        if(root == nullptr){
            root = new Node(item);
            return true;
        }
        insertHelper(root, item);
        return true;
    }

    Node* inorderNode(Node* node){
        Node* orderNode = node->left;
        while(orderNode->right != nullptr){
            orderNode = orderNode->right;
        }
        return orderNode;
    }

    Node* getParent(Node* lookRoot, Node* findNode){
        if(findNode == root){return nullptr;}
        if(findNode == lookRoot->left || findNode == lookRoot->right){return lookRoot;}
        if(lookRoot->value > findNode->value){return getParent(lookRoot->left, findNode);}
        else{return getParent(lookRoot->right, findNode);}
    }

    bool remove(T item) {
        // implement remove here
        // return true if item was removed, false if item wasn't in the tree
        if(root == nullptr){return false;}
        Node* node = containsHelper(root, item);
        if(node == nullptr){return false;}
        tSize--;
        Node* parent = getParent(root, node);
        int branchCount = 0;
        int branchSide = -1;
        if(node->left != nullptr){branchCount++; branchSide = 0;}
        if(node->right != nullptr){branchCount++; branchSide = 1;}
        
        int sideOfParent = 0;
        if (parent == nullptr){sideOfParent = -1;}
        else if(node->value > parent->value){sideOfParent = 1;}
        Node* sideNode = nullptr;

        switch (branchCount)
        {
        case 0:
            if (sideOfParent == -1){ root = nullptr; }
            else{
                if(sideOfParent == 0){parent->left = nullptr;}
                else{parent->right = nullptr;}
            }
            delete node;
            break;

        case 1:
            sideNode = branchSide == 0 ? node->left : node->right;
            if (sideOfParent == -1){root = sideNode;}
            else{
                if(sideOfParent == 0){parent->left = sideNode;}
                else{parent->right = sideNode;}
            }
            delete node;
            break;
        
        case 2:
            T tempVal = inorderNode(node)->value;
            remove(tempVal);
            node->value = tempVal;
            break;
        }
        return true;
    }

    Node* containsHelper(Node* node, T item) const {
        int val = node->value;
        if(item == val) { return node; }
        if(item < val && node->left != nullptr){return containsHelper(node->left, item);}
        if(item > val && node->right != nullptr){return containsHelper(node->right, item);}
        return nullptr;
    }

    bool contains(T item) const {
        // implement contains here
        // return true if item is in the tree, false otherwise
        if(root != nullptr){return containsHelper(root, item) != nullptr;}
        return false;
    }

    void clear() {
        // implement clear here
        // remove all nodes from the tree
        if(root == nullptr){return;}
        stack<Node*> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.empty()){
            Node* next = nodeStack.top();
            nodeStack.pop();
            if(next->left != nullptr){nodeStack.push(next->left);}
            if(next->right != nullptr){nodeStack.push(next->right);}
            delete next;
        }
        tSize = 0;
        root = nullptr;
    }

    int size() const {
        // implement size here
        // return the number of nodes in the tree
        return tSize;
    }
};
