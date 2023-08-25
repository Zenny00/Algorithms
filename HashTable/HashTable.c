// Name: HashTable.c
// Author: Zenny00
// Date: 7/29/2023
// Description: Implementation of a simple hash table in C

#include <stdio.h>
#include <stdlib.h>

// Define a struct to hold key value pairs
// Both the key and the value are strings
typedef struct item {
	char *key;
	char *value;
};

// Define a struct for the hash table
// Holds an array of points to hash items
typedef struct HashTable {
	item **items;
	int capacity;
	int size;
};

// ====================================================================
// 													LINKED LIST
// ====================================================================

typedef struct LinkedList {
	item *ht_item;
	struct LinkedList *next;
};

// Allocate memory for the linked list
struct LinkedList *allocate_list() {
	struct LinkedList *list = (struct LinkedList *) malloc(sizeof(struct LinkedList));
	return list;
}



// Return the index for the hash table
// Simple / bad hash function, simply sum the values of the string ASCII
unsigned long hash_function(char *str, int capacity) {
	unsigned long index = 0;

	for (int i = 0; str[i]; i++) {
		index += str[i];
	}

	return index % capacity;
}

// A function to create a new item
// Allocate memory for the struct and the strings contained within
// Returns a pointer to the new item struct
struct item *create_item(char *key, char *value) {
	// Allocate the memory for a new hash table item 
	struct item *new_item = (item *) malloc(sizeof(item));
	
	// Check for successful allocation
	if (!new_item) {
		printf("Insufficient memory available!\n");
		exit(1);
	}

	// Allocate memory for the key and value strings
	new_item->key = (char *) malloc((strlen(key) + 1) * sizeof(char));
	new_item->value = (char *) malloc((strlen(value) + 1) * sizeof(char));

	// Check for successful allocation
	if (!new_item->key || !new_item->value) {
		printf("Insufficient memory available!\n");
		exit(1);
	}

	// Copy over the strings passed in as parameters to the strings in the struct
	if (!strcpy(new_item->key, key) || !strcpy(new_item->value, value)) {
		printf("Failed to create new item!\n");
		exit(1);
	}

	return new_item;
}

// Used to deallocate the space used for a hash table item
void free_item(struct item *item) {
	free(item->key);
	free(item->value);
	free(item);
}

// Create the HashTable and initialize all values to NULL
// Returns a pointer to the new HashTable
struct HashTable *create_table(int capacity) {
	struct HashTable *hash_table = (struct HashTable *) malloc(sizeof(struct HashTable));

	// Check for successful allocation
	if (!hash_table) {
		printf("Insufficient memory available!\n");
		exit(1);
	}
	
	// Initialize capacity and current size
	hash_table->capacity = capacity;
	hash_table->size = 0;

	// We use calloc here as we need to allocate space for a given number of items with a certain size
	// The calloc() function reserves storage space for an array of num elements, each of length size bytes. - IBM.com
	hash_table->items = (struct item**) calloc(hash_table->capacity, sizeof(struct item*));
	
	// Check for successful allocation
	if (!hash_table->items) {
		printf("Insufficient memory available!\n");
		exit(1);
	}

	// Initalize all elements of the items array to NULL
	for (int i = 0; i < hash_table->capacity; i++) {
		hash_table->items[i] = NULL;
	}

	// Return a reference to the hash table
	return hash_table;
}

// Clear table and free all memory
// Use the clear item utility function
void free_table(struct HashTable *hash_table) {
	// Loop through and clear all table items
	for (int i = 0; i < hash_table->capacity; i++) {
		// Pass a pointer to the item to the utility function
		struct item *curr_item = hash_table->items[i];
		if (curr_item) {
			free_item(curr_item);
		}
	}

	// Free the array
	free(hash_table->items);
	// Free the table
	free(hash_table);
}

void hash_table_insert(struct HashTable *hash_table, char *key, char *value) {
	// Create new item
	item *new_item = create_item(key, value);

	// Compute the table index
	int index = hash_function(key);

	// Get the table item based off the index
	struct item *current_item = hash_table->items[index];

	// Check if the space is empty in the table
	if (!current_item) {
		// Check if the table is full
		if (hash_table->capacity == hash_table->size) {
			printf("Cannot insert. Hash table is full!\n");
			free_item(new_item);
			return;
		}
	
		// Add the item to the table
		hash_table->items[index] = new_item;
		hash_table->size++;
	} else {
		// Otherwise we have a collision
		// Compare the keys
		if (strcmp(current_item->key, key) == 0) {
			strcpy(hash_table->items[index]->value, value);
			return;
		} else {
			handle_collision(hash_table, item);
			return;
		}
	}
}

// Takes a key and searches the hash table, returns the value if it exists
char *hash_table_search(struct HashTable *hash_table, char *key) {
	// Calculate the index
	int index = hash_function(key);
	struct item *current_item = hash_table->items[index];

	// Determine if the item is NULL
	if (!current_item) {
		// Check for matching key
		if (strcmp(current_item->key, key) == 0) {
			return current_item->value;
		}
	}

	// If the item doesn't exist, return NULL
	return NULL; 
}

// Print utility function
void print_search(struct HashTable *hash_table, char *key) {
	char *value;

	// If the searched value doesn't exist, print an error message
	if ((value = hash_table_search(hash_table, key)) == NULL) {
		printf("Key: %s doesn't exist\n", key);
		return;
	} else {
		// Otherwise print the key value pair
		printf("Key: %s | Value: %s\n", key, value);
	}
}
