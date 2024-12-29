#include <iostream>
#include <queue>
#include<cmath>
using namespace std;


struct  Node {
	int key;
	Node* left;
	Node* right;
	int height;
};

Node* newNode(int data) {
	Node* p = new Node;
	p->key = data;
	p->left = p->right = NULL;
	p->height = 1;
	return p;
}


int balanceIndex(Node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 0;
	if (root->left == NULL) return root->right->height;
	if (root->right == NULL) return -root->left->height;
	return root->right->height - root->left->height;
}
int calHeight(Node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	if (root->left == NULL) return 1 + root->right->height;
	if (root->right == NULL) return 1 + root->left->height;
	return 1 + max(root->left->height, root->right->height);
}

Node * rotateRight(Node* root) {
	Node* leftNode = root->left;
	root->left = leftNode->right;
	leftNode->right = root;
	root->height = calHeight(root);
	leftNode->height = calHeight(leftNode);
	return leftNode;
}
Node* rotateLeft(Node* root) {
	Node* rightNode = root->right;
	root->right = rightNode->left;
	rightNode->left = root;
	root->height = calHeight(root);
	rightNode->height = calHeight(rightNode);
	return rightNode;
}

Node* insertNode(Node* root, int data) {
	Node* pNode = newNode(data);
	if (root == NULL) return pNode;
	if (data > root->key) {
		root->right = insertNode(root->right, data);
	}
	else if (data < root->key) {
		root->left = insertNode(root->left, data);
	}
	else {
		return root;
	}
	Node* leftNode = root->left;
	Node* rightNode = root->right;

	if (leftNode == NULL) {
		root->height = rightNode->height + 1;
	}
	else if (rightNode == NULL) {
		root->height = leftNode->height + 1;
	}
	else {
		root->height = max(leftNode->height, rightNode->height) + 1;
	}

	int blcIndex = balanceIndex(root);

	if (blcIndex >= 2) {
		if (balanceIndex(root->right) < 0) {
			root->right = rotateRight(root->right);
		}
		root = rotateLeft(root);
	}
	else if (blcIndex <= -2) {
		if (balanceIndex(root->left) > 0) {
			root->left = rotateLeft(root->left);
		}
		root = rotateRight(root);
	}
	

	return root;
}

Node* searchNode(Node* root, int data) {
	if (root == NULL) return NULL;
	if (root->key == data) return root;
	if (data > root->key) return searchNode(root->right, data);
	return searchNode(root->left, data);
}

Node* findMin(Node* root) {
	if (root == NULL) return NULL;
	Node* cur = root;
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur;
}


Node* deleteNode(Node* root, int data) {
	if (root == NULL) return NULL;
	if (data > root->key) {
		root->right = deleteNode(root->right, data);
	}
	else if (data < root->key) {
		root->left = deleteNode(root->left, data);
	}
	else {
		if (root->left == NULL && root->right == NULL) {
			delete root;
			return NULL;
		}
		else if (root->left == NULL) {
			Node* temp = root->right;
			delete root;
			root = temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			delete root;
			root = temp;
		}
		else {
			Node* min = findMin(root->right);
			root->key = min->key;
			root->right = deleteNode(root->right, min->key);
		}
	}
	root->height = calHeight(root);
	int blcIndex = balanceIndex(root);
	if (blcIndex >= 2) {
		if (balanceIndex(root->right) < 0) {
			root->right = rotateRight(root->right);
		}
		root = rotateLeft(root);
	}
	else if (blcIndex <= -2) {
		if (balanceIndex(root->left) > 0) {
			root->left = rotateLeft(root->left);
		}
		root = rotateRight(root);
	}
	return root;
}
void NLR(Node* root) {
	if (root == NULL) return;
	cout << root->key << " ";
	NLR(root->left);
	NLR(root->right);
}
void LRN(Node* root) {
	if (root == NULL) return;
	LRN(root->left);
	LRN(root->right);
	cout << root->key << " ";
}
void LNR(Node* root) {
	if (root == NULL) return;
	LNR(root->left);
	cout << root->key << " ";
	LNR(root->right);
}

void LevelOrder(Node* root) {
	if (root == NULL) return;
	queue <Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* p = q.front();
		cout << p->key << " " ;
		q.pop();
		if (p->left != NULL) {
			q.push(p->left);
		}
		if (p->right != NULL) {
			q.push(p->right);
		}
	}
}

bool isFull(Node* root) {
	if (root == NULL) return true;
	if (root->left == NULL && root->right == NULL) return true;
	if (root->left != NULL && root->right != NULL) {
		return isFull(root->left) && isFull(root->right);
	}
	return false;
}
bool isComplete(Node* root) {
	if (root == NULL) return true;
	queue <Node*> q;
	q.push(root);
	bool nullafter = false;
	while (!q.empty()) {
		Node* p = q.front();
		q.pop();
		if (p == NULL) {
			nullafter = true;
		}
		else  {
			if (nullafter)return false;
			q.push(p->left);
			q.push(p->right);
		}
	}
	return true;
}
int countNode(Node* root) {
	if (root == NULL) return 0;
	return 1 + countNode(root->left) + countNode(root->right);
}
bool isPerfect(Node* root) {
	if (root == NULL) return true;
	int h = root->height;
	return countNode(root) == pow(2, h) - 1;

}
void printSpecialNodes(Node* root) {
	if (root == NULL) return;
	printSpecialNodes(root->left);
	if (root->right != NULL && root->left != NULL &&root->left->key != 0 && root->right->key % root->left->key == 0) {
		cout << root->key << " ";

	}
	printSpecialNodes(root->right);
}

