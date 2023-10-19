#include <iostream>
#include "header1.h"      
        

        //Defualt constructo of AVL_Node class
		AVL_Node :: AVL_Node(int x)
        {
            data=x;
            left=NULL;
            right=NULL;
            bf=0;
        }