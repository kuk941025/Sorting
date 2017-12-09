#ifndef _HEAP_H
#define _HEAP_H

#define MAX_HEAP	100000

typedef enum { false, true } bool;


typedef struct {
	int data;
	int priority;
} HNode;

typedef struct {
	HNode *items;
	int num;
} Heap;


// Make a heap empty.
void InitHeap(Heap *pheap, int n);
// check whether a heap is empty.
bool IsEmpty(Heap *pheap);
// Check whether a heap is full.
bool IsFull(Heap *pheap);

// Get a parent index for a given index.
int GetParent(int idx);
// Get a left child index for a given index.
int GetLChild(int idx);
// Get a right child index for a given index.
int GetRChild(int idx);
// Get a child index with high priority between two child nodes.
int GetHighPrioityChild(Heap* pheap, int idx);

// Insert a node to the heap.
void Insert(Heap *pheap, int data, int priority);
// Remove the maximum data from the heap.
int Delete(Heap *pheap);

#endif _HEAP_H