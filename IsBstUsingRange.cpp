//17th Feb 2017 (6th) - Is this Tree a BST?

#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int val;
    struct Node *l;
    struct Node *r;
};

Node *AddNode(int val)
{
    Node *t = new Node();
    t->val = val;
    t->l = NULL;
    t->r = NULL;

    return t;
}

Node *BuildTree()
{
    Node *root = AddNode(40);
    root->l = AddNode(30);
    root->r = AddNode(50);

    root->l->l = AddNode(10);
    root->l->r = AddNode(35);
    root->r->l = AddNode(45);
    root->r->r = AddNode(80);

    root->l->l->l = AddNode(10);
    root->l->l->r = AddNode(12);
    root->l->r->l = AddNode(33);
    root->l->r->r = AddNode(37);
    root->r->l->l = AddNode(41);
    root->r->l->r = AddNode(48);
    root->r->r->l = AddNode(60);
    root->r->r->r = AddNode(200);

    return root;
}

bool IsBST(Node *root, int low, int high)
{
    if (root == NULL)
        return true;

    if(!(root->val >= low && root->val <= high))
        return false;

    return IsBST(root->l, low, root->val) && IsBST(root->r, root->val+1, high);
}

int main()
{
    Node *root = BuildTree();

    if(IsBST(root, 0, 500))
        cout << "BST!";
    else
        cout << "NOT BST!";

    getchar();

    return 0;
}
