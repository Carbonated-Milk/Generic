#pragma once
#include <stack>
using std::stack;
#include <algorithm>
using std::max;

template<class T>
class AVL {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;
        int height;

        Node(T v) : left(nullptr), right(nullptr), value(v), height(1) {}
    };

    Node* root;
    int tSize;

    AVL() {
        // implement the contructor here
        root = nullptr;
        tSize = 0;
    }

    ~AVL() {
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
        rebalance(root);
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

    bool removeHelper(T item) {
        // implement remove here
        // return true if item was removed, false if item wasn't in the tree
        Node* node = containsHelper(root, item);
        if(node == nullptr){return false;}
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
            removeHelper(tempVal);
            node->value = tempVal;
            break;
        }
        return true;
    }

    bool remove(T item) {
        if(root == nullptr || !contains(item)){return false;}
        tSize--;
        bool success = removeHelper(item);
        rebalance(root);
        return success;
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

    ///// REBALENCE STUFF  /////

    // Hint: you might find it helpful to write an update_height function that takes
    // a Node* and updates its height field based on the heights of its children
    void update_height(Node*& root){ 
        root->height = max(get_height(root->right), get_height(root->left)) + 1;
    }

    int get_height(Node*& root){ 
        if(root == nullptr){return 0;}
        return root->height;
    }

    void promote_left(Node*& root) {
        // implement promote_left here
        Node* new_root = root->left;
        root->left = new_root->right;
        new_root->right = root;
        root = new_root;
        update_height(root->right);
        update_height(root);
    }

    void promote_right(Node*& root) {
        // implement promote_right here
        Node* new_root = root->right;
        root->right = new_root->left;
        new_root->left = root;
        root = new_root;
        update_height(root->left);
        update_height(root);
    }

    int getNodeBalance(Node*& root){
        if(root == nullptr){return 0;}
        return get_height(root->left) - get_height(root->right);
    }

    void rebalance(Node*& root) {
        // implement rebalance here
        if(root == nullptr){return;}
        if(root->left == nullptr && root->right == nullptr){return;}

        rebalance(root->left);
        rebalance(root->right);

        update_height(root);

        if(getNodeBalance(root) > 1){
            if(getNodeBalance(root->left) < 0){
                promote_right(root->left);
            }
            promote_left(root);
        }
        if(getNodeBalance(root) < -1){
            if(getNodeBalance(root->right) > 0){
                promote_left(root->right);
            }
            promote_right(root);
        }
    }
};
