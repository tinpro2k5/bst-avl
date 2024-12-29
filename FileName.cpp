#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left = NULL;
    Node* right = NULL;
};

// Corrected max function
int max(int a, int b) {
    return (a < b) ? b : a;
}

// Calculate height of the binary tree
int calculateHeight(Node* root) {
    if (root == NULL) return 0;
    return 1 + max(calculateHeight(root->left), calculateHeight(root->right));
}

// Helper function to find and print the longest path
void help(Node* root, int maxlen, int* store, int index) {

    if (index == maxlen) {
        // Print the path in reverse order
        for (int i = 0; i < index; i++) {
            cout << store[i] << " ";
        }
        cout << endl;
        return;
    }
    if (root == NULL) return;

    store[index] = root->data;
    help(root->left, maxlen, store, index + 1);
    help(root->right, maxlen, store, index + 1);
}

// Function to print the longest path
void printLongestPath(Node* root) {
    int maxlen = calculateHeight(root);
    int* store = new int[maxlen]();
    help(root, maxlen, store, 0);
    delete[] store; // Free allocated memory
}



// Hàm in các nút theo mức
void level(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);
    int level = 1;

    while (!q.empty()) {
        int size = q.size(); // Số nút trong mức hiện tại
        cout << "Level " << level << ": ";

        for (int i = 0; i < size; i++) {
            Node* p = q.front();
            q.pop();

            cout << p->data << " ";

            if (p->left != NULL) {
                q.push(p->left);
            }
            if (p->right != NULL) {
                q.push(p->right);
            }
        }

        cout << endl;
        level++; // Tăng mức sau khi in xong một mức
    }
}


Node* createTreefromSortedArr(int* arr, int L, int R) {
    if (L <= R) {
        int M = (L + R) / 2; // Chọn phần tử giữa làm gốc
        Node* p = new Node(arr[M]); // Tạo nút gốc với giá trị ở giữa
        p->left = createTreefromSortedArr(arr, L, M - 1); // Đệ quy với nửa bên trái
        p->right = createTreefromSortedArr(arr, M + 1, R); // Đệ quy với nửa bên phải
        return p;
    }
    return NULL; // Khi mảng rỗng hoặc không hợp lệ
}


void biggestBranch(Node* root, int cum_sum, int& cur_max) {
    if (root == NULL) return; // Nếu cây rỗng, thoát đệ quy

    // Cộng giá trị của nút hiện tại vào tổng cộng dồn
    cum_sum += root->data;

    // Nếu là nút lá, cập nhật tổng lớn nhất
    if (root->left == NULL && root->right == NULL) {
        if (cum_sum > cur_max) {
            cur_max = cum_sum;
        }
    }

    // Đệ quy tìm tổng lớn nhất cho cây con trái và cây con phải
    biggestBranch(root->left, cum_sum, cur_max);
    biggestBranch(root->right, cum_sum, cur_max);
}


Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
    // Nếu root là NULL, trả về NULL
    if (!root) return nullptr;

    // Nếu giá trị của p và q đều nhỏ hơn root, tìm trong cây con bên trái
    if (p->data < root->data && q->data < root->data) {
        return lowestCommonAncestor(root->left, p, q);
    }
    // Nếu giá trị của p và q đều lớn hơn root, tìm trong cây con bên phải
    else if (p->data > root->data && q->data > root->data) {
        return lowestCommonAncestor(root->right, p, q);
    }
    // Nếu một trong hai node có giá trị bằng root hoặc nằm ở hai bên trái và phải, root là tổ tiên chung gần nhất
    else {
        return root;
    }
}


// Structure to represent an interval
struct Interval {
    int low, high;

    Interval(int l = 0, int h = 0) : low(l), high(h) {}
};

// Structure to represent a node in the interval tree
struct Node {
    Interval interval; // The interval stored in this node
    int max;           // Maximum high value in the subtree rooted at this node
    Node* left;
    Node* right;
    int height;

    Node(Interval i) : interval(i), max(i.high), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of the tree
int height(Node* node) {
    return node ? node->height : 0;
}

// Function to update the height of a node
void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

// Function to get the balance factor of a node
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Insert a new interval into the interval tree
Node* insert(Node* root, Interval i) {
    if (!root)
        return new Node(i);

    if (i.low < root->interval.low)
        root->left = insert(root->left, i);
    else
        root->right = insert(root->right, i);

    // Update the max value of this node
    root->max = max(root->max, i.high);

    // Update height
    updateHeight(root);

    // Balance the node
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && i.low < root->left->interval.low)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && i.low >= root->right->interval.low)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && i.low >= root->left->interval.low) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && i.low < root->right->interval.low) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Check if two intervals overlap
bool doOverlap(Interval i1, Interval i2) {
    return (i1.low <= i2.high && i2.low <= i1.high);
}

// Find an interval that overlaps with the given interval
Interval* overlapSearch(Node* root, Interval i) {
    if (!root)
        return nullptr;

    if (doOverlap(root->interval, i))
        return &root->interval;

    if (root->left && root->left->max >= i.low)
        return overlapSearch(root->left, i);

    return overlapSearch(root->right, i);
}



