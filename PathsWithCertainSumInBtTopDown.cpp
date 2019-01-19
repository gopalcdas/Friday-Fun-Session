#include <iostream>
#include <unordered_map>

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
  Node *root = AddNode(1);
  root->l = AddNode(2);
  root->r = AddNode(-1);

  root->l->l = AddNode(1);
  root->l->r = AddNode(-2);
  root->r->l = AddNode(1);
  root->r->r = AddNode(2);

  root->l->l->l = AddNode(-2);
  root->l->r->l = AddNode(1);

  root->l->r->l->l = AddNode(3);

  return root;
}

void AddCount(unordered_map<int, int> hash, int key, int &count)
{
  auto a = hash.find(key);
  if (a != hash.end())
    count = count + a->second;
}

void IncrementHash(unordered_map<int, int> &hash, int key)
{
  auto a = hash.find(key);
  if (a != hash.end())
    a->second++;

  hash.insert(make_pair(key, 1));
}

void DecrementHash(unordered_map<int, int> &hash, int key)
{
  auto a = hash.find(key);
  if (a != hash.end())
    a->second--;

  if(a->second == 0)
    hash.erase(key);
}

void CountSum(Node *root, int targetSum, int runningSum, unordered_map<int, int> &hash, int &count)
{
  if (root == NULL)
    return;

  runningSum = runningSum + root->val;
  if (runningSum == targetSum)
    count++;

  int diff = runningSum - targetSum;
  AddCount(hash, diff, count);
	
  IncrementHash(hash, runningSum);
  CountSum(root->l, targetSum, runningSum, hash, count);
  CountSum(root->r, targetSum, runningSum, hash, count);
  DecrementHash(hash, runningSum);
}

int main()
{
  Node *root = BuildTree();

  unordered_map<int, int> hash;
  int count = 0;
  int targetSum = 2;
  CountSum(root, targetSum, 0, hash, count);

  cout << count << endl;

  getchar();

  return 0;
}
