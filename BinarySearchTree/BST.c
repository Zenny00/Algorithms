// Name: BST.c
// Author: Zenny00
// Date: 8/30/2023
// Description: Implementation of a Binary Search Tree (BST) in C

#include <stdio.h>
#include <stdlib.h>

// Tree node struct
// value: Holds the current value of the node
// right: Holds a reference to the right subnode
// left: Holds a reference to the left subnode
struct Node {
	int value;
	struct Node *right;
	struct Node *left;
};

// Search function
// Recursively searches the BST for a give value
// If found, a reference to that value will be returned
struct Node *searchBST(struct Node *root, int target) {
	// Check if the tree is empty or if the target is the current subtree root
	if (!root || root->value == target) {
		return root;
	}

	// If the target is greater than the current subtree root, move right
	// Otherwise, move left
	if (target > root->value) {
		return searchBST(root->right, target);
	} else {
		return searchBST(root->left, target);
	}
}

// Utility function to return the minimum value in the tree
struct Node *findMinimum(struct Node *root) {
	// If the tree is empty, return NULL
	if (!root) {
		return NULL;
	}

	// Check if the left subtree is NULL
	if (root->left != NULL) {
		return findMinimum(root->left);
	}

	// When the left subtree is NULL we have reached the minimum value
	return root;
}

// Utility function to return the maximum value in the tree
struct Node *findMaximum(struct Node *root) {
	// If the tree is empty, return NULL
	if (!root) {
		return NULL;
	}

	// Check if the right subtree is NULL
	if (root->right != NULL) {
		return findMaximum(root->right);
	}

	// When the right subtree is NULL we have reached the maximum value
	return root;
}

// Create a new node for the BST
struct Node *createNode(int value) {
	// Create a new pointer and allocate the space for the node
	struct Node *new_node = NULL;
	new_node = (struct Node *) malloc(sizeof(struct Node));

	// Assign values to the fields 
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

// Insert a node into the tree
// After node is inserted, return a reference to the root
struct Node *insertNode(struct Node *root, int value) {
	// Check if the root is NULL. If so, we place the new node at the root
	if (!root) {
		return createNode(value);
	}

	// Otherwise insert into the correct location recursively
	if (value > root->value) {
		root->right = insertNode(root->right, value);
	} else {
		root->left = insertNode(root->left, value);
	}

	return root;
}

// Delete a node from the tree and correctly link the tree after removal
struct Node *deleteNode(struct Node *root, int value) {
	// If the root is NULL the value doesn't exist in the tree
	if (!root) {
		return NULL;
	}

	// Check each side of the tree
	if (value > root->value) {
		root->right = deleteNode(root->right, value);
	} else if (value < root->value) {
		root->left = deleteNode(root->left, value);
	} else {
		// No subtrees
		// If there are no subtrees the node can be removed freely
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		// One subtree
		} else if (root->left == NULL || root->right == NULL) {
			struct Node *temp = NULL;
			if (root->left == NULL) {
				temp = root->right;
			} else {
				temp = root->left;
			}
			free(root);
			return temp;
		}
		// Two subtrees
		else {
			struct Node *temp = findMinimum(root->right);
			root->value = temp->value;
			root->right = deleteNode(root->right, temp->value);
		}
	}
	return root;
}

// Display the tree in order
void inOrder(struct Node *root) {
	// Check for NULL root
	if (root) {
		inOrder(root->left);
		printf(" %d ", root->value); // Print the value of the root
		inOrder(root->right);
	}
}

// Display the tree in preorder
void preOrder(struct Node *root) {
	// Check for NULL root
	if (root) {
		printf(" %d ", root->value); // Print the value of the root
		preOrder(root->left);
		preOrder(root->right);
	}
}

// Display the tree in postorder
void postOrder(struct Node *root) {
	// Check for NULL root
	if (root) {
		postOrder(root->left);
		postOrder(root->right);
		printf(" %d ", root->value); // Print the value of the root
	}
}

void printMenu() {
	printf("1) Add value\n");
	printf("2) Remove value\n");
	printf("3) Display tree\n");
	printf("4) Quit\n");
}

int main(int argc, char **argv) {
	// Holds the current BST
	struct Node *root = NULL;
	// Holds the user's input
	int user_in = 0;
	int tree_value = -1;

	while (user_in != 4) {
		printMenu();
		printf("Please select an option: ");
		do {
			scanf("%d", &user_in);
			if (user_in < 1 || user_in > 4) {
				printf("Invalid input. Please enter a value from 1-4.\n");
			}
		} while (user_in < 1 || user_in > 4);

		if (user_in == 1) {
			printf("Please enter a value to insert: ");
			scanf("%d", &tree_value);
			root = insertNode(root, tree_value);
		} else if (user_in == 2) {
			printf("Please enter a value to delete: ");
			scanf("%d", &tree_value);
			root = deleteNode(root, tree_value);
		} else if (user_in == 3) {
			if (!root) {
				printf("Empty tree\n");
			}
			inOrder(root);
		} else {
			printf("Exiting... Goodbye!\n");
		}

		printf("\n");
	}
}
