#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node
{
	int key;
	Node* left;
	Node* right;
};

Node* newNode(int data);
Node* insert(Node* root, int data);
Node* search(Node* root, int data);
Node* _delete(Node* root, int data); // tên hàm bị trùng từ khóa delete 
void NLR(Node* root);
void LNR(Node* root);
void LRN(Node* root);
void LevelOrder(Node* root);
int height(Node* root); // tính độ cao từ node root là 0
int countNode(Node* root);
int sumNode(Node* root);
int countLeaf(Node* root);
int countLess(Node* root, int x);
int countGreater(Node* root, int x);
int main() {
	Node* tree = NULL;
	tree = insert(tree, 8);
	tree = insert(tree, 6);
	tree = insert(tree, 5);
	tree = insert(tree, 7);
	tree = insert(tree, 10);
	tree = insert(tree, 9);

	cout << "Pre-Order: ";
	NLR(tree);
	cout << endl << "In-Order: ";
	LNR(tree);
	cout << endl << "Post-Order: ";
	LRN(tree);

	cout << endl << "After Delete: ";
	tree= _delete(tree, 8);
	cout << endl << "Level-Order: ";
	LevelOrder(tree);

	cout <<endl << "Height (start from 0 with root) : " << height(tree);
	cout << endl << "Count Node: " << countNode(tree);
	cout << endl << "Sum Node: " << sumNode(tree);
	cout << endl << "Count Leaf: " << countLeaf(tree);
	cout << endl << "Count Less than x = 7: " << countLess(tree, 7);
	cout << endl << "Count Greater x = 7: " << countGreater(tree, 7);
	return 0;

}


Node* newNode(int data) {
	Node* newNode = new Node;
	if (!newNode) {
		cout << "Error Creating New Node";
		return NULL;
	}
	newNode->key = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}
Node* insert(Node* root, int data) {
	if (root == NULL) return newNode(data);
	if (data == root->key) return root;
	if (data > root->key) {
		root->right = insert(root->right, data);
	}
	else {
		root->left = insert(root->left, data);

	}
	return root;
}
Node* search(Node* root, int data) {
	if (root == NULL) return NULL;
	if (root->key == data) return root;
	if (data > root->key) return search(root->right, data);
	return search(root->left, data);
}

Node* minNode(Node* root) {
	if (root == NULL) return NULL;
	Node* cur = root;
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur;
}

Node* _delete(Node* root, int data) {
	if (root == NULL) return NULL;
	if (data > root->key) {
		root->right = _delete(root->right, data);
	}
	else if (data < root->key) {
		root->left = _delete(root->left, data);
	}
	else {
		if (root->left == NULL) {
			Node* temp = root->right;
			delete root;
			return temp;
		}
		if (root->right == NULL) {
			Node* temp = root->left;
			delete root;
			return temp;
		}
		else{
			Node* minRight = minNode(root->right);
			root->key = minRight->key;
			root->right = _delete(root->right, minRight-> key);
		}
	}
	return root;
}

void NLR(Node* root) {
	if (root == NULL) return;
	cout << root->key << " ";
	NLR(root->left);
	NLR(root->right);
}
void LNR(Node* root) {
	if (root == NULL) return;
	LNR(root->left);
	cout << root->key << " ";
	LNR(root->right);
}
void LRN(Node* root) {
	if (root == NULL) return;
	LRN(root->left);
	LRN(root->right);
	cout << root->key << " ";
}

void LevelOrder(Node* root) {
	if (root == NULL) return;
	queue <Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();
		cout << cur->key << " ";
		if (cur->left != NULL) {
			q.push(cur->left);
		}
		if (cur->right != NULL) {
			q.push(cur->right);
		}
	}


}
int height(Node* root) {
	if (root == NULL) return -1;
	return 1 + max(height(root->left), height(root->right));

}
int countNode(Node* root) {
	if (root == NULL) return 0;
	return 1 + countNode(root->left) + countNode(root->right);
}
int sumNode(Node* root) {
	if (root == NULL) return 0;
	return root->key + sumNode(root->left) + sumNode(root->right);
}
int countLeaf(Node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	return countLeaf(root->left) + countLeaf(root->right);	
}
int countLess(Node* root, int x) {
	if (root == NULL) return 0;
	if (root->key < x) return 1 + countLess(root->left, x) + countLess(root->right, x);
	return countLess(root->left, x) + countLess(root->right, x);
}
int countGreater(Node* root, int x) {
	if (root == NULL) return 0;
	if (root->key > x) return 1 + countGreater(root->left, x) + countGreater(root->right, x);
	return countGreater(root->left, x) + countGreater(root->right, x);
}