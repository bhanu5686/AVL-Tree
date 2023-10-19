#include <iostream>
#include "header2.h"
using namespace std;


int main() {
    AVL_Tree avl;
	//int a[10]={4,7,1,9,3,5,2,8,6,10};
	//int a[10]={1,5,8,6,9,10,7,8,9,10};
    int a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	//int a[10]={10,9,8,7,6,1,2,3,4,5};
	for (int i=0;i<10;i++) {
	    avl.AVL_Insert(a[i]);
	}
    avl.AVL_Search(25);
    avl.AVL_Delete(4);
    avl.AVL_Print("avltree.png");

    cout<<"\n\nExecuted Successfully...\n";
	return 0;
}
