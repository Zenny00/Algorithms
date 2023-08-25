// Name: TowersOfHanoi.c
// Author: Zenny00
// Date: 8/24/2023
// Description: Implementation of the Towers Of Hanoi game in C

#include <stdio.h>
#include <stdlib.h>

void towersOfHanoi(int n, char from, char to, char temp) {
	// If the number of disks left is one, move from the starting to ending rod
	if (n == 1) {
		printf("\nMove disk 1 from rod %c to rod %c\n", from, to);
		return;
	}

	towersOfHanoi(n-1, from, temp, to);
	printf("\nMove disk %d from rod %c to rod %c", n, from, to);
	towersOfHanoi(n-1, temp, to, from);
}

int main(int argc, char **argv) {
	// Number of disks
	int n;

	// Prompt user for input
	printf("Enter the number of disks: ");
	
	if (!scanf("%d", &n)) {
		printf("Failed to get input. Exiting.\n");
		exit(1);
	}

	// Call the recursive Towers Of Hanoi function
	towersOfHanoi(n, 'A', 'B', 'C');
	return 0;
}
