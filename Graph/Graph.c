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
