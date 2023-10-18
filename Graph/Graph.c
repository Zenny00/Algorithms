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
}
