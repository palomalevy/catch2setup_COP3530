#ifndef AVL_H
#define AVL_H

#include <vector>

class AVL {
private:
    // forward declaration; real Node lives in the .cpp
    struct Node;
    Node* root = nullptr;

    // helpers (private on purpose)
    int   getHeight(Node* node);
    void  updateHeight(Node* node);
    int   getBalanceFactor(Node* node);
    Node* rotateRight(Node* y); // same idea as rightRotate
    Node* rotateLeft(Node* x);  // same idea as leftRotate
    Node* insertHelper(Node* node, int value);
    Node* findMinValueNode(Node* node);
    Node* removeHelper(Node* node, int value);
    void  inorderHelper(Node* node, std::vector<int>& out);
    void  destroyTree(Node* node);

public:
    // simple, do-nothing stubs (same behavior as your version)
    AVL() = default;
    ~AVL() = default;

    void insert(int /*value*/) {
        // stub: not implemented yet
    }

    void remove(int /*value*/) {
        // stub: not implemented yet
    }

    std::vector<int> inorder() const {
        // stub: returns empty traversal
        return {};
    }
};

#endif // AVL_H