//13ᵗʰ Dec 2018 (82ᶰᵈ) - BST to Doubly Linked List

#include <iostream>

using namespace std;

struct BiNode
{
	int val;

	BiNode *left;  // head
	BiNode *right; // tail
};

BiNode *CreateNode(int val)
{
	BiNode *n = new BiNode();
	
	n->val = val;
	n->left = NULL;
	n->right = NULL;

	return n;
}

BiNode *CreateTree()
{
	BiNode *root = CreateNode(20);
	root->left = CreateNode(10);
	root->left->left = CreateNode(5);
	root->left->right = CreateNode(15);
	root->right = CreateNode(30);
	root->right->left = CreateNode(25);
	root->right->right = CreateNode(35);

	return root;
}

BiNode * BuildMidNode(BiNode *root)
{
	root->left = root;
	root->right = root;

	return root;
}

BiNode *Merge(BiNode *leftHead, BiNode *rightHead)
{
	BiNode *leftTail = leftHead->left;
	BiNode *rightTail = rightHead->left;

	leftTail->right = rightHead;
	rightTail->right = leftHead;

	leftHead->left = rightTail;

	return leftHead;
}

BiNode *Merge(BiNode *leftHead, BiNode *midNode, BiNode *rightHead)
{
	BiNode *result = leftHead == NULL ? midNode : Merge(leftHead, midNode);
	result = rightHead == NULL ? result : Merge(result, rightHead);

	return result;
}

BiNode *BuildLl(BiNode *root)
{
	if (root == NULL)
		return NULL;	

	BiNode* leftHead = BuildLl(root->left);
	BiNode* rightHead = BuildLl(root->right);
	
	BiNode* midNode = BuildMidNode(root);

	return Merge(leftHead, midNode, rightHead);
}

void PrintLl(BiNode *head)
{
	if (head == NULL)
	{
		cout << "empty list" << endl;
		return;
	}

	BiNode *tail = head->left;
	BiNode *node = head;

	while (1)
	{
		cout << node->val << " ";

		if (node == tail)
			break;

		node = node->right;
	}

	cout << endl;
}

int main()
{
	BiNode *root = CreateTree();

	BiNode *head = BuildLl(root);

	PrintLl(head);

	getchar();

	return 0;
}
