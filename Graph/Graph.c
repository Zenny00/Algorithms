// Implementation of a simple graph data structure using an adjacency list.
// Name: Zenny00
// Date: 10/17/2023
// File: Graph.c

#include <stdio.h>
#include <stdlib.h>

// Macro defining the maximum size of the graph in the number of nodes
#define MAX_SIZE 10

// Struct to define the graph data structure
struct Graph {
	struct Node *head[MAX_SIZE]; // Define array of Node pointers, this is the adjacency list
};

// Struct to define the node data type
struct Node {
	int dest;
	struct Node *next;
};

// Defines the edge of a graph from source to destination node
struct Edge {
	int src;
	int dest;
};

// Create the graph given the edges
struct Graph *createGraph(struct Edge edges[], int n) {
	struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph)); // Allocate space for the graph

	// Set all array values to NULL
	for (int i = 0; i < MAX_SIZE; i++) {
		graph->head[i] = NULL;
	}

	// Add edges to the graph
	for (int i = 0; i < n; i++) {
		int src = edges[i].src;
		int dest = edges[i].dest;

		// Allocate space for the new node
		struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;

		// Update the graph
		newNode->next = graph->head[src];
		graph->head[src] = newNode;
	}

	return graph;
}

// Clear the memory allocated for the graph
void freeGraph(struct Graph *graph) {
	for (int i = 0; i < MAX_SIZE; i++) {
		struct Node *ptr = graph->head[i];
		while (ptr != NULL) {
			struct Node *tmp = ptr;
			ptr = ptr->next;
			free(tmp);
		}
	}
	free(graph);
}

// Print the representation of the graph
void printGraph(struct Graph *graph) {
	for (int i = 0; i < MAX_SIZE; i++) {
		struct Node *ptr = graph->head[i];
		while (ptr != NULL) {
			printf("(%d -> %d)\t", i, ptr->dest);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

int main(int argc, char **argv) {
	// (x, y) pair represents an edge traveling from x to y
	struct Edge edges[] = {
		{1, 2}, {2, 3}, {3, 1}, {3, 4}, {3, 5}, {4, 2}, {5, 2}, {5, 6}, {6, 7}
	};

	// Number of edges
	int n = sizeof(edges)/sizeof(edges[0]);

	// Build the graph
	struct Graph *graph = createGraph(edges, n);

	// Print the adjacency list
	printGraph(graph);

	freeGraph(graph); // Free the memory allocated for the graph
	
	return 0;
}
