
#ifndef AVL_Tree_H
#define AVL_Tree_H

#include "header1.h"   

class AVL_Tree
{
    private:
        AVL_Node *root,*head;
        bool AVL_Search(AVL_Node*,int);
        void printAVL(AVL_Node*, FILE*);
        void printLevelOrder(AVL_Node*,FILE*);

    public:
        AVL_Tree();
        void AVL_Search(int k);
        void AVL_Insert(int k);
        void AVL_Delete(int k);
        void AVL_Print(const char*);
        ~AVL_Tree();
        
};

#endif