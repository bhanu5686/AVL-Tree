
#ifndef AVL_Node_H
#define AVL_Node_H

class AVL_Node
{
    friend class AVL_Tree;
    private:
        int data;
        int bf;
        AVL_Node *left;
        AVL_Node *right;
    public:
        AVL_Node(int);
};

#endif