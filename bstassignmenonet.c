#include <stdio.h>
#include <stdlib.h>
/*
REGISTRATION NUMBER  |  NAME
---------------------|-----------
SCT221-0207/2023 -> MARYLYNE NASHIPAE
SCT221-0255/2023 -> GIDEON KIPAMET

Question:
Consider a binary search tree (BST) represented by an array shown below
30
20
40
10
25
35
Write a C program with functions to do the following tasks
i) Create the BST represented by an array above
ii) Delete any node from the BST
iii) Print the height of the BST
iv)
Print the level and height of any node in the BST
45
5
15
*/

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int item) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node *insert(struct Node *node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    return node;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int height(struct Node *node) {
    if (node == NULL) return 0;
    else {
        int left_height = height(node->left);
        int right_height = height(node->right);
        if (left_height > right_height) return (left_height + 1);
        else return (right_height + 1);
    }
}

struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL) return root;

    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int getNodeLevel(struct Node *root, int key, int level) {
    if (root == NULL) return 0;
    if (root->key == key) return level;
    int downlevel = getNodeLevel(root->left, key, level + 1);
    if (downlevel != 0) return downlevel;
    downlevel = getNodeLevel(root->right, key, level + 1);
    return downlevel;
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node *root = NULL;

    // Create BST
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("Inorder traversal of the BST: ");
    inorder(root);
    printf("\n");

    // Delete node with key 25
    int key_to_delete = 25;
    root = deleteNode(root, key_to_delete);
    printf("BST after deleting %d: ", key_to_delete);
    inorder(root);
    printf("\n");

    // Print height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Print level and height of node with key 15
    int key_to_find = 15;
    int level = getNodeLevel(root, key_to_find, 1);
    int node_height = height(root) - (level - 1);
    printf("Level of %d: %d\n", key_to_find, level);
    printf("Height of %d: %d\n", key_to_find, node_height);

    return 0;
}
