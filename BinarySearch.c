// Name: BinarySearch.c
// Author: Zenny00
// Date: 7/26/2023
// Description: Implementation of BinarySearch in C

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int left, int right, int target) {
	// Returns an int specifying the index the requested target is located at
	// Return -1 if the specified target is not found
	
	// Loop through the array until the left index is greater than or equal to the right
	while (left <= right) {
		// Calculate the midpoint
		int mid = left + (right - left) / 2;

		// Check if the value at the midpoint index is the requested value
		if (arr[mid] == target) {
			return mid;
		}

		// If the target value is greater than the value at the midpoint index, ignore everything below it
		if (arr[mid] < target) {
			left = mid + 1;
		} else {
			// Otherwise, ignore the upper half
			right = mid - 1;
		}
	}

	// If the function has not returned before the end of the loop the value was not present in the array, return -1
	return -1;
}

void selectionSort(int *arr, int size) {
	int min = 0, temp = 0;

	for (int i = 0; i < size - 1; i++) {
		// Start at the beginning of the unsorted array
		min = i;
		for (int j = i + 1; j < size; j++) {
			// Check if the current element is smaller than the current min
			if (arr[j] < arr[min]) {
				min = j;
			}
		}

		// Swap the current min to the correct location
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

void printArray(int *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void fillArray(int *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("Enter element at index %d: ", i);
		if (scanf("%d", &array[i]) == 0) {
			printf("Error getting user input, exiting\n");
			exit(1);
		}
	}
}

int main(int argc, char **argv) {
	// The program will take user input for the array size
	int arr_size = 0;
	// The target element the user wishes to find the index of
	int target = 0;

	// Prompt the user for an integer
	printf("Please enter the size of the array you would like to populate: ");
	if (scanf("%d", &arr_size) == 0) {
		printf("Error getting user input, exiting\n");
		exit(1);
	}

	// Array to hold the user's entries
	int *array = (int *)malloc(arr_size * sizeof(int));
	if (!array) {
		printf("Failed to allocate memory.");
		exit(1);
	}

	// Fill the array with entries
	fillArray(array, arr_size);
	
	// Sort the array
	selectionSort(array, arr_size);

	// Print the array after being sorted 
	printf("The sorted array: ");
	printArray(array, arr_size);

	// Get the target element from the user
	printf("Please enter the target element: ");
	if (scanf("%d", &target) == 0) {
		printf("Error getting user input, exiting\n");
		exit(1);
	}

	// Use binary search to find the element's index
	int index = binarySearch(array, 0, arr_size - 1, target);

	// Print the index to the user
	if (index == -1) {
		printf("Element does not exist in the give array\n");
	} else {
		printf("%d is located at index %d\n", array[index], index);
	}

	// Free the memory allocated for the array
	free(array);
}
