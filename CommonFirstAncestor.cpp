// 17th Jan 2019 (87th) – Common First Ancestor of Two Nodes in a Binary Tree with All Unique Values
// https://gopalcdas.com/2017/10/10/topics-in-friday-fun-session/

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

  root->l->l->l = AddNode(11);
  root->l->l->r = AddNode(12);
  root->l->r->l = AddNode(33);
  root->l->r->r = AddNode(37);
  root->r->l->l = AddNode(41);
  root->r->l->r = AddNode(48);
  root->r->r->l = AddNode(60);
  root->r->r->r = AddNode(200);

  return root;
}

int CommonFirstAncestor(Node *root, int f, int s, Node **cp)
{
  if (root == NULL)
    return 0;

  int lc = CommonFirstAncestor(root->l, f, s, cp);
  int rc = CommonFirstAncestor(root->r, f, s, cp);

  int totalCount = lc + rc + ((root->val == f || root->val == s) ? 1 : 0);

  if (*cp == NULL && totalCount == 2)
    *cp = root;

  return totalCount;
}

int main()
{
  Node *root = BuildTree();

  Node *cp = NULL;
  CommonFirstAncestor(root, 33, 37, &cp);

  if (cp == NULL)
    cout << "not found";
  else
    cout << cp->val << endl;

  getchar();

  return 0;
}
