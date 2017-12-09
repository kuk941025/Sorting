#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

typedef int* Data;
int* generate_random(int n, int op);
void copy_arr(int *arr1, int *arr2, int n);
float selection_sort(Data list, int n);
float bubble_sort(Data list, int n);
float InsertionSort(Data list, int n);
float ShellSort(Data list, int n);
void prnArr(Data list, int n);
float callMerge(Data list, int left, int right, int n);
void MergeSort(Data list, int left, int right, int n);
float IterMergeSort(Data list, int n);
float heap_sort(Data arr, int n);
float quick(Data list, int left, int right, int n, int isRnd);
void QuickSort(Data list, int left, int right, int n, int isRnd);
int main() {
	int n, *rndArr, *cpyArr;
	scanf("%d", &n);
	cpyArr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < 2; i++) {
		rndArr = generate_random(n, i); //0 random !0 = sorted
		//prnArr(rndArr, n);
//		copy_arr(rndArr, cpyArr, n);
		if (!i)
			printf("Random array\n");
		else
			printf("Sorted array\n");
		printf("Selection sort: %lf\n", selection_sort(cpyArr, n));


		copy_arr(rndArr, cpyArr, n);
		printf("Bubble sort: %lf\n", bubble_sort(cpyArr, n));
	
		copy_arr(rndArr, cpyArr, n);
		printf("Insertion sort: %lf\n", InsertionSort(cpyArr, n));
		//prnArr(cpyArr, n);

		copy_arr(rndArr, cpyArr, n);
		printf("Shell sort: %lf\n", ShellSort(cpyArr, n));

		copy_arr(rndArr, cpyArr, n);
		printf("Merge sort: %lf\n", callMerge(cpyArr, 0, n -1, n));
		//prnArr(cpyArr, n);

		copy_arr(rndArr, cpyArr, n);
		printf("Iterative Merge sort: %lf\n", IterMergeSort(cpyArr, n));

		copy_arr(rndArr, cpyArr, n);
		printf("Heap sort: %lf\n", heap_sort(cpyArr, n));

		copy_arr(rndArr, cpyArr, n);
		printf("Quick sort: %lf\n", quick(cpyArr, 0, n - 1, n, 0));
	

		copy_arr(rndArr, cpyArr, n);
		srand(time(NULL));
		printf("Randomized Quick sort: %lf\n", quick(cpyArr, 0, n - 1, n, 1));

		printf("\n\n");
	}
	//prnArr(cpyArr, n);
	return 0;
}
void prnArr(Data list, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}
void copy_arr(int *arr1, int *arr2, int n) {
	int i;
	for (i = 0; i < n; i++)
		arr2[i] = arr1[i];
}
int* generate_random(int n, int op) {
	int i, *arr;
	arr = (int*)malloc(sizeof(int) * n);
	if (op == 0) {
		srand(time(NULL));
		for (i = 0; i < n; i++)
			arr[i] = rand() % 1000;

	}
	else {
		int num = n - 1;
		for (i = 0; i < n; i++) {
			arr[i] = num--;
		}
	}
	return arr;
}
float selection_sort(Data list, int n) {
	int min, temp;
	clock_t start, end;
	float result;
	
	start = clock();
	temp = 0;
	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			// Find an index with the minimum element.
			if (list[j] < list[min])
				min = j;
		}
		// Exchange the minimum element and the i-th element.
		temp = list[i];
		list[i] = list[min];
		list[min] = temp;

	}
	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}

float bubble_sort(Data list, int n)
{
	float result;
	clock_t start, end;
	int temp;
	start = clock();
	for (int i = n - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			// Compare each pair of adjacent items.
			if (list[j] < list[j + 1])
			{
				// Swap if they are in the wrong order.
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}

float InsertionSort(Data list, int n)
{
	clock_t start, end;
	float result;
	int j, key;

	start = clock();
	for (int i = 1; i < n; i++)
	{
		key = list[i];// Choose the i-th element.
		for (j = i - 1; j >= 0; j--) {
			// If the j-th element is greater than key,
			// move to the next position.
			if (key > list[j])
				list[j + 1] = list[j];
			else
				break;
		}
		// Otherwise, move the key to the (j+1)-th element.
		list[j + 1] = key;
	}
	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}
void IncInsertionSort(int* list, int first, int last, int k)
{
	int i, j, key;
	// Sort every k-th element
	for (i = first + k; i < last; i = i + k)
	{
		key = list[i]; // Choose the i-th element.
					   // If the j-th element is greater than key,
					   // move to the next position with k interval.
		for (j = i - k; j >= first && key > list[j]; j = j - k)
			list[j + k] = list[j];
		list[j + k] = key;
	}
}
float ShellSort(Data list, int n)
{
	clock_t start, end;
	float result;
	start = clock();
	// Sort every k-th element by reducing from n/2 to 1.
	for (int k = n / 2; k > 0; k /= 2)
	{
		// Choose the k-th element as the odd.
		if ((k % 2) == 0) k++;
		for (int i = 0; i < k; i++)
			IncInsertionSort(list, i, n, k);
	}
	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}

void Merge(Data list, int left, int mid, int right, int n)
{
	int *sorted;
	int first = left, second = mid + 1, i = left;
	sorted = (int*)malloc(sizeof(int) * n);
	// Merge two lists by comparing elements in sequence.
	while (first <= mid && second <= right) {
		if (list[first] >= list[second])
			sorted[i++] = list[first++];
		else
			sorted[i++] = list[second++];
	}

	// For remaining items, add them in sequence.
	if (first > mid)
		for (int j = second; j <= right; j++)
			sorted[i++] = list[j];
	else
		for (int j = first; j <= mid; j++)
			sorted[i++] = list[j];

	// Copy the sorted list to the list.
	for (int j = left; j <= right; j++)
		list[j] = sorted[j];

	free(sorted);

}
float callMerge(Data list, int left, int right, int n) {
	clock_t start, end;
	float result;
	start = clock();
	MergeSort(list, left, right, n);
	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}
void MergeSort(Data list, int left, int right, int n)
{

	if (left < right)
	{
		int mid = (left + right) / 2; 	// Equal partitioning
		MergeSort(list, left, mid, n);		// Sorting sublists
		MergeSort(list, mid + 1, right, n);	// Sorting sublists
		Merge(list, left, mid, right, n);	// Merging two sublists
	}

}

float IterMergeSort(Data* list, int n)
{
	clock_t start, end;
	float result;
	start = clock();
	
	// Merge subarrays in bottom up manner.  First merge subarrays of
	// size 1 to create sorted subarrays of size 2, then merge subarrays
	// of size 2 to create sorted subarrays of size 4, and so on.
	for (int size = 1; size <= n - 1; size = 2 * size)
	{
		// Pick starting point of different subarrays of current size
		for (int left_start = 0; left_start < n - 1; left_start += 2 * size)
		{
			// Find ending point of left subarray.
			// mid+1 is starting  point of right
			int mid = min(left_start + size - 1, n - 1);
			int right_end = min(left_start + 2 * size - 1, n - 1);
			
			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
			Merge(list, left_start, mid, right_end, n);
		}
	}
	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}
float heap_sort(Data arr, int n) {
	Heap heap;
	float result;
	clock_t start, end;
	int i;
	InitHeap(&heap, n);
	start = clock();
	for (i = 0; i < n; i++)
		Insert(&heap, arr[i], arr[i]);
	i = 0;
	while (!IsEmpty(&heap))
		arr[i++] = Delete(&heap);

	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}

int Partition(Data list, int left, int right, int isRnd){ //4240
	int pIdx;
	int pivot = list[left], temp;
	int low = left + 1, high = right;

	if (isRnd != 0) {
		pIdx = left + rand() % (right - left + 1);
		pivot = list[pIdx];
	}
	while (1) {
		while (low < right && list[low] < pivot)
			low++;	// Move low until pivot < L[low]
		while (high > left && list[high] >= pivot)
			high--;	// Move high until pivot >= L[low]

		if (low < high)
			// Swap list[low] and list[high].
		{
			temp = list[low];
			list[low] = list[high];
			list[high] = temp;
		}

		else break;
	}
	temp = list[left];
	list[left] = list[high];
	list[high] = temp;
	return high;// return the pivot position.

}

float quick(Data list, int left, int right, int n, int isRnd) {
	float result;
	clock_t start, end;
	start = clock();
	QuickSort(list, left, right, n, isRnd);
	end = clock();
	result = (float)(end - start) / CLOCKS_PER_SEC;
	return result;
}
void QuickSort(Data list, int left, int right, int n, int isRnd)
{

	if (left < right) {
		// The mid refers to the pivot position.
		int mid = Partition(list, left, right, n, isRnd);

		// All elements are less than the pivot.
		QuickSort(list, left, mid - 1, n, isRnd);

		// All elements are greater than the pivot.
		QuickSort(list, mid + 1, right, n, isRnd);
	}


}
