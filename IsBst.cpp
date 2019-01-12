#include <iostream>

using namespace std;

const int MaxAllowedDiff = 1;

struct Node
{
  int val;
  Node *l;
  Node *r;
};

Node *CreateNode(int val)
{
  Node *n= new Node();
  n->val = val;
  n->l = NULL;
  n->r = NULL;

  return n;
}

Node *BuildTree()
{
  Node *root = CreateNode(1);
	
  root->l = CreateNode(2);
  root->r = CreateNode(3);

  root->l->l = CreateNode(4);
  root->l->r = CreateNode(5);

  root->l->l->l = CreateNode(8);
  root->l->l->r = CreateNode(9);

  root->l->l->l->l = CreateNode(10);

  root->r->l = CreateNode(6);
  root->r->r = CreateNode(7);

  root->r->l->l = CreateNode(11);
  root->r->r->l = CreateNode(12);

  return root;
}

int IsBst(Node *root)
{
  if (root == NULL)
    return 0;

  int lc = IsBst(root->l);
  int rc = IsBst(root->r);

  if (abs(lc - rc) > MaxAllowedDiff)
    return INT_MIN;

  return lc > rc ? lc + 1 : rc + 1;
}

int main()
{
  Node *root = BuildTree();

  int len = IsBst(root);

  if (len == INT_MIN)
    cout << "unbalanced";
  else
    cout << "balanced";

  getchar();

  return 0;
}
