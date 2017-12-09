
#include "heap.h"

// Make a heap empty.
void InitHeap(Heap *pheap, int n)
{
	pheap->num = 0;
	pheap->items = (HNode*)malloc(sizeof(HNode) * n);
}

// check whether a heap is empty.
bool IsEmpty(Heap *pheap)
{
	return pheap->num == 0;
}

// Check whether a heap is full.
bool IsFull(Heap *pheap)
{
	return pheap->num == MAX_HEAP;
}

// Get a parent index for a given index.
int GetParent(int idx)
{
	return idx / 2;
}

// Get a left child index for a given index.
int GetLChild(int idx)
{
	return idx * 2;
}

// Get a right child index for a given index.
int GetRChild(int idx)
{
	return idx * 2 + 1;
}

// Get a child index with high priority between two child nodes.
int GetHighPrioityChild(Heap* pheap, int idx)
{
	if (GetLChild(idx) > pheap->num)	// No child nodes exist.
		return 0;
	else if (GetLChild(idx) == pheap->num) // Exist a left child only.
		return GetLChild(idx);
	else // Choose a child node with the highest priority.
	{
		int left = GetLChild(idx), right = GetRChild(idx);
		if (pheap->items[left].priority > pheap->items[right].priority)
			return left;
		else
			return right;
	}
}

// Insert a node to the heap.
void Insert(Heap *pheap, int data, int priority )
{
	HNode newNode;
	int idx = pheap->num + 1;

	// Compare the new node with its parent.
	while (idx > 1)
	{
		int parent = GetParent(idx);
		if (priority > pheap->items[parent].priority)
		{
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else
			break;
	}

	newNode.data = data;
	newNode.priority = priority;

	pheap->items[idx] = newNode;
	pheap->num++;
}

// Remove the maximum data from the heap.
int Delete(Heap *pheap)
{
	int max = pheap->items[1].data;
	HNode last = pheap->items[pheap->num];
	int parent = 1, child;

	while (child = GetHighPrioityChild(pheap, parent))
	{
		if (last.priority < pheap->items[child].priority)
		{
			pheap->items[parent] = pheap->items[child];
			parent = child;
		}
		else
			break;
	}

	pheap->items[parent] = last;
	pheap->num--;

	return max;
}
