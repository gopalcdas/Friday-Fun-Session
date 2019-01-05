#include <iostream>
#include <unordered_map>

using namespace std;

struct Node
{
	int val;
	struct Node *l;
	struct Node *r;

	unordered_map<int, int> sumList;
	int counter;
};

Node *CreateNode(int val)
{
	Node *node = new Node();
	node->val = val;
	node->l = NULL;
	node->r = NULL;
	node->counter = 0;

	return node;
}

Node *GetData()
{
	Node *root = CreateNode(10);
	root->l = CreateNode(5);
	root->l->l = CreateNode(3);
	root->l->l->l = CreateNode(3);
	root->l->l->r = CreateNode(-2);
	
	root->l->r = CreateNode(2);
	root->l->r->r = CreateNode(1);

	root->r = CreateNode(-3);
	root->r->r = CreateNode(11);

	return root;
}

void AddToHash(Node **t, int val, int counter)
{
	auto v = (*t)->sumList.find(val);
	if (v == (*t)->sumList.end())
	{
		(*t)->sumList.insert(pair<int, int>(val, counter));
		return;
	}

	v->second = v->second + counter;
}

void CreateSumList(Node **t, Node **cn, int targetSum)
{
	AddToHash(t, (*t)->val + (*cn)->val, 1);
	if (targetSum == (*t)->val + (*cn)->val)
		(*t)->counter++;

	for (auto it = (*cn)->sumList.begin(); it != (*cn)->sumList.end(); ++it)
	{
		AddToHash(t, (*t)->val + it->first, it->second);
		if (targetSum == (*t)->val + it->first)
			(*t)->counter = (*t)->counter + it->second;
	}		
}

void PrintSumList(Node **t)
{
	cout << "Node: " << (*t)->val  << " Counter: " << (*t)->counter << endl;
	for (auto it = (*t)->sumList.begin(); it != (*t)->sumList.end(); ++it)
		cout << "(" << it->first << ", " << it->second << ") ";

	cout << endl;
}

void Count(Node **t, int targetSum)
{
	if (t == NULL)
		return;

	if ((*t)->l != NULL)
		Count(&(*t)->l, targetSum);

	if ((*t)->r != NULL)
		Count(&(*t)->r, targetSum);

	if ((*t)->l != NULL)
	{
		CreateSumList(t, &((*t)->l), targetSum);
		(*t)->counter = (*t)->counter + (*t)->l->counter;
	}		
	
	if ((*t)->r != NULL)
	{
		CreateSumList(t, &((*t)->r), targetSum);
		(*t)->counter = (*t)->counter + (*t)->r->counter;
	}

	//PrintSumList(t);
}

int main()
{
	Node * root = GetData();

	Count(&root, 8);

	cout << "Counter: " << root->counter << endl;

	getchar();

	return 0;
}
