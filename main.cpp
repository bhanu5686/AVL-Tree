#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class AVL_Node
{
    friend class AVL_Tree;
    private:
        int data;
        int bf;
        AVL_Node *left;
        AVL_Node *right;
    public:
        AVL_Node(int x)
        {
            data=x;
            left=NULL;
            right=NULL;
            bf=0;
        }
};

class AVL_Tree
{
    private:
        AVL_Node *root,*head;
        bool AVL_Search(AVL_Node *root,int k)
        {
            if(root==NULL)
                return false;
            else if(root->data==k)
                return true;
            else if(k<=root->data)
                return AVL_Search(root->left,k);
            else
                return AVL_Search(root->right,k);
        }


        void printAVL(AVL_Node* root, FILE* stream)
        {
            fprintf(stream, "digraph BST {\n");
            fprintf(stream, "    head [fontname=\"Arial\"];\n");

            if (!root)
                fprintf(stream, "\n");
            else
                printLevelOrder(root, stream);

            fprintf(stream, "}\n");
        }

        void printLevelOrder(AVL_Node *root,FILE* stream)
        {
            static int c = 1;
            static int cnt = 1;
            if (root == NULL)
                return;

            queue<pair<AVL_Node *,int>> q;
            q.push(make_pair(root,c));
            c++;

            while (q.empty() == false)
            {
                pair<AVL_Node *,int> p = q.front();
                fprintf(stream, "    node_number%d [label=\"%d , %d\"];\n",p.second, p.first->data,p.first->bf);
                q.pop();

                if (p.first->left != NULL)
                {
                    q.push(make_pair(p.first->left,c));
                    fprintf(stream, "    node_number%d -> node_number%d;\n",p.second, c);
                    c++;
                }
                else
                {
                    fprintf(stream, "    node_number%d -> null_number%d;\n",p.second, cnt);
                    fprintf(stream, "    null_number%d [shape=point];\n",cnt++);
                }

                if (p.first->right != NULL)
                {
                    q.push(make_pair(p.first->right,c));
                    fprintf(stream, "    node_number%d -> node_number%d;\n",p.second, c);
                    c++;
                }
                else
                {
                    fprintf(stream, "    node_number%d -> null_number%d;\n",p.second, cnt);
                    fprintf(stream, "    null_number%d [shape=point];\n",cnt++);
                }

            }
        }

    public:
        AVL_Tree()
        {
            root=NULL;
            head=NULL;
        }
        void AVL_Search(int k);
        void AVL_Insert(int k);
        void AVL_Delete(int k);
        void AVL_Print(const char *filename);
        ~AVL_Tree()
        {
            delete head;
            delete root;
        }

};
void AVL_Tree :: AVL_Search(int k)
{
    if(AVL_Search(head->right,k))
        cout<<endl<<k<<" is found\n";
    else
        cout<<endl<<k<<" is not found\n";
}
void AVL_Tree :: AVL_Insert(int k)
{
    try
    {
        if(AVL_Search(root,k))
            throw k;
        else
        {
            if(root == NULL)
            {
                root = new AVL_Node(k);
                head=new AVL_Node(1);
                head->right=root;
                root=head->right;
                return;
            }
            AVL_Node *t,*s,*p,*q,*r;
            int a,f=0;
            t=head;
            s=head->right;
            p=s;

            while (true)
            {
                if(k<=p->data)
                {
                    q=p->left;
                    if(q==NULL)
                    {
                        q=new AVL_Node(k);
                        p->left=q;
                        break;
                    }
                    else if(q->bf!=0)
                    {
                        t=p;s=q;
                    }
                }
                else
                {
                    q=p->right;
                    if(q==NULL)
                    {
                        q=new AVL_Node(k);
                        p->right=q;
                        break;
                    }
                    else if(q->bf!=0)
                    {
                        t=p;s=q;
                    }
                }
                p=q;
            }
            if(k <= s->data)
            {
                a=1;
                r=s->left;
                p=r;
            }
            else
            {
                a=-1;
                r=s->right;
                p=r;
            }

            while(p!=q)
            {
                if(k <= p->data)
                {
                    p->bf=1;
                    p=p->left;
                }
                else if(k > p->data)
                {
                    p->bf=-1;
                    p=p->right;
                }
                else
                {
                    p=q;
                }
            }
            //B(S)==0
            if(s->bf==0)
            {
                s->bf=a;
                head->data++;
                root=head->right;
                return;
            }
            //B(s)=-a
            else if(s->bf == -1 * a)
            {
                s->bf=0;
                root=head->right;
                return;
            }
            //B(s)=a
            else if(s->bf==a && s->bf < 0)
            {
                if(r->bf==a)
                {
                    //RR Rotation
                    p=r;
                    s->right=r->left;
                    r->left=s;
                    s->bf=0;
                    r->bf=0;
                    //goto a10
                }

                else if(r->bf == -a)
                {
                    //RL Rotation
                    p=r->left;
                    r->left=p->right;
                    p->right=r;
                    s->right=p->left;
                    p->left=s;

                    if(p->bf==a)
                    {
                        s->bf=-a;
                        r->bf=0;
                    }

                    else if(p->bf==0)
                    {
                        s->bf=0;
                        r->bf=0;
                    }

                    else if(p->bf == -a)
                    {
                        s->bf=0;
                        r->bf=a;
                    }

                    p->bf=0;
                }
            }

            //B(s)=a
            else if(s->bf==a && s->bf > 0)
            {
                if(r->bf==a)
                {
                    //LL Rotation
                    p=r;
                    s->left=r->right;
                    r->right=s;
                    s->bf=0;
                    r->bf=0;
                    //goto a10
                }

                else if(r->bf == -a)
                {
                    //LR Rotation
                    p=r->right;
                    r->right=p->left;
                    p->left=r;
                    s->left=p->right;
                    p->right=s;

                    if(p->bf==a)
                    {
                        s->bf=-a;
                        r->bf=0;
                    }

                    else if(p->bf==0)
                    {
                        s->bf=0;
                        r->bf=0;
                    }

                    else if(p->bf == -a)
                    {
                        s->bf=0;
                        r->bf=a;
                    }

                    p->bf=0;
                }
            }



            if(s==t->right)
                t->right=p;
            else
                t->left=p;
            root=head->right;
            return;
        }
    }
    catch(int num)
    {
        cout<<endl<<num<<" is already present in AVL Tree"<<endl;
    }
}




void AVL_Tree :: AVL_Delete(int key)
{
    try
    {
        if(!AVL_Search(root,key))
            throw key;
        else
        {

			AVL_Node *r = head->right; // initally pointing to root of the tree, but it will point to the node going to be deleted

            // x -> Node to be balanced
            // y -> parent of the Node to be balanced
            // z -> left/right child of the Node to be balanced

            AVL_Node *x, *y, *z;

            stack<AVL_Node*> st; // saves the st to the Node
            st.push(head); //pushing the head (dummy) Node

            while(r)
            {
                if(key < r->data)
                {
                    st.push(r);
                    r = r->left;
                }
                else if(key > r->data)
                {
                    st.push(r);
                    r = r->right;
                }
                else
                {
                    break;
                }
            }

                // if r has a single child or no child (leaf)
                if(r->left==NULL || r->right==NULL)
                {
                    AVL_Node *prev = st.top();
                    AVL_Node *cnt;

                    if(r->left==NULL)
                        cnt=r->right;
                    else
                        cnt=r->left;


                    if(!cnt)
                    {
                        cnt = r;
                        if(r == prev->left)
                            prev->left = NULL;
                        else prev->right = NULL;
                            r = NULL;
                    }
                    else
                    {
                        r->data = cnt->data;
                        r->bf = cnt->bf;
                        r->left = cnt->left;
                        r->right = cnt->right;
                    }
                    delete cnt;
                }
                // Node to be deleted has both the children
                else
                {
                    st.push(r);
                    AVL_Node *succ = r->right; //finding the successor of r
                    while(succ->left!=NULL)
                    {
                        st.push(succ);
                        succ = succ->left;
                    }
                    r->data = succ->data;
                    key = succ->data; // because the Node that is being deleted is the successor

                    AVL_Node *cnt;

                    if(succ->left!=NULL)
                        cnt = succ->left;
                    else
                        cnt = succ->right;

                    AVL_Node *prev = st.top();

                    if(!cnt)
                    {
                        cnt = succ;
                        if(succ == prev->left)
                            prev->left = NULL;
                        else prev->right = NULL;
                            succ = NULL;
                    }
                    else
                    {
                        succ->data = cnt->data;
                        succ->bf = cnt->bf;
                        succ->left = cnt->left;
                        succ->right = cnt->right;
                    }
                    delete cnt;
                }




            while(st.top() != head)
            {
                x = st.top();
                int a;

                if(key < x->data)
                    a = 1;
                else
                    a = -1;

                st.pop();
                y = st.top();

                if(x->bf == a)
                {
                    x->bf = 0;
                    continue;
                }
                else if(x->bf == 0)
                {
                    x->bf = -1*a;
                    root=head->right;
                    return;
                }
                else
                {
                    if(x->bf == 1)
                        z=x->left;
                    else
                        z=x->right;

                    //single rotation
                    if(z->bf == -1*a)
                    {
                        if(a == -1)
                        {
                            //LL Rotation
                            r = z;
                            x->left = z->right;
                            z->right = x;
                            x->bf = 0;
                            z->bf = 0;
                        }
                        else if(a == 1)
                        {
                            //RR Rotation
                            r = z;
                            x->right = z->left;
                            z->left = x;
                            x->bf = 0;
                            z->bf = 0;
                        }
                    }
                    //single rotation
                    else if(z->bf == 0)
                    {
                        if(a == -1)
                        {
                            //LL Rotation
                            r = z;
                            x->left = z->right;
                            z->right = x;
                            z->bf = a;
                        }
                        else if(a == 1)
                        {
                            //RR Rotation
                            r = z;
                            x->right = z->left;
                            z->left = x;
                            z->bf = a;
                        }
                    }
                    //double rotation
                    else if(z->bf == a)
                    {
                        if(a == -1)
                        {
                            //LR Rotation
                            r = z->right;
                            z->right = r->left;
                            r->left = z;
                            x->left = r->right;
                            r->right = x;
                            if(r->bf == 0)
                            {
                               x->bf = 0;
                               z->bf = 0;
                            }
                            else if(r->bf == 1)
                            {
                                x->bf = -1;
                                z->bf = 0;
                            }
                            else
                            {
                                x->bf = 0;
                                z->bf = 1;
                            }
                            r->bf = 0;
                        }
                        else if(a == 1)
                        {
                            //RL Rotation
                            r = z->left;
                            z->left = r->right;
                            r->right = z;
                            x->right = r->left;
                            r->left = x;

                            if(r->bf == 0)
                            {
                               x->bf = 0;
                               z->bf = 0;
                            }
                            else if(r->bf == 1)
                            {
                                x->bf = 0;
                                z->bf = -1;
                            }
                            else
                            {
                                x->bf = 1;
                                z->bf = 0;
                            }

                            r->bf = 0;
                        }
                    }

                    if(r->bf == 1 || r->bf == -1)
                    {
                        if(x == y->right)
                            y->right = r;
                        else
                            y->left = r;
                        root=head->right;
                        return;
                    }
                }
                if(x == y->right)
                    y->right = r;
                else
                    y->left = r;
                root=head->right;
            }
        }
    }
    catch(int num)
    {
        cout<<endl<<num<<" is not present in AVL Tree"<<endl;
    }
}





void AVL_Tree :: AVL_Print(const char *filename)
{
            FILE *stream,*fp;

            stream=fopen("input.graphviz","w+");

            if(stream==NULL)
                cout<<"cant open file";
            else
            {
                printAVL(head->right,stream);
            }
            fclose(stream);

            fp=fopen("input.graphviz","r");

            if(fp==NULL)
                cout<<"image cannot be created"<<endl;
            else
            {
                string st(filename);
                string s = "dot -Tpng input.graphviz -o "+st;
                system(s.c_str());
                //system(st.c_str());  
            }
            fclose(fp);
}



int main() {
    AVL_Tree avl;
	//int a[10]={4,7,1,9,3,5,2,8,6,10};
	//int a[10]={1,5,8,6,9,10,7,8,9,10};
    int a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	//int a[10]={10,9,8,7,6,1,2,3,4,5};
	for (int i=0;i<10;i++) {
	    avl.AVL_Insert(a[i]);
	}

    //avl.AVL_Delete(7);
    avl.AVL_Print("avltree.png");


    cout<<"\n\nExecuted Successfully...\n";
	return 0;
}
