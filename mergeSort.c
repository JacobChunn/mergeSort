#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isInOrder(int* array, int arrLen);
bool compareSortedUnsortedArrayContents(int* sortedArr, int* unsortedArr, int arrLen);
int getOccurrences(int* array, int arrLen, int value);
void randomizeArray(int* array, int arrLen, int lower, int upper);
void printArray(int* array, int arrLen);
void mergeSort(int* array, int left, int right);
void merge(int* array, int left, int middle, int right);

void main() {
	int lower = -100;
	int upper = 100;
	int arrLen = 10000;
	int array[arrLen];
	int origArrayCopy[arrLen];


	randomizeArray(array, arrLen, lower, upper);
	memcpy(origArrayCopy, array, sizeof(array));

	printArray(array, arrLen);
	mergeSort(array, 0, arrLen - 1);
	printArray(array, arrLen);

	printf("Original Array is in order: %s\n",
		isInOrder(origArrayCopy, arrLen) ? "true" : "false");

	printf("Sorted Array is in order: %s\n",
		isInOrder(array, arrLen) ? "true" : "false");

	printf("Original Array contains same values as Unsorted Array: %s\n",
		compareSortedUnsortedArrayContents(array, origArrayCopy, arrLen) ? "true" : "false");
}

bool isInOrder(int* array, int arrLen) {
	if (arrLen == 0) {
		return true;
	}

	for (int i = 0; i < arrLen - 1; i++) {
		if (array[i] > array[i + 1]) {
			return false;
		}
	}
	return true;
}

bool compareSortedUnsortedArrayContents(int* sortedArr, int* unsortedArr, int arrLen) {
	if (arrLen == 0) {
		return true;
	}
	
	int compareValue = sortedArr[0];
	for (int i = 0; i < arrLen - 1; i++) {
		if (compareValue != sortedArr[i + 1]) {
			compareValue = sortedArr[i + 1];
		} else {
			continue;
		}

		int sortedOccurrences = getOccurrences(sortedArr, arrLen, compareValue);
		int unsortedOccurrences = getOccurrences(sortedArr, arrLen, compareValue);

		if (sortedOccurrences != unsortedOccurrences)
			return false;
	}

}

int getOccurrences(int* array, int arrLen, int value) {
	int occurrences = 0;
	for (int i = 0; i < arrLen; i++) {
		if (array[i] == value) occurrences++;
	}
	return occurrences;
}

void randomizeArray(int* array, int arrLen, int lower, int upper) {
	for (int i = 0; i < arrLen; i++) {
		array[i] = (rand() % (upper - lower)) + lower;
	}
}

void printArray(int* array, int arrLen) {
	for (int i = 0; i < arrLen; i++) {
		printf("%d", array[i]);
		if (i != arrLen - 1) {
			printf(", ");
		} else {
			printf("\n");
		}
	}
}

void mergeSort(int* array, int left, int right) {
	if (left < right) {
		int middle = ((right - left) / 2) + left;

		mergeSort(array, left, middle);

		mergeSort(array, middle + 1, right);

		merge(array, left, middle, right);
	}
}

void merge(int* array, int left, int middle, int right) {


	int leftArrSize = middle - left + 1;
	int rightArrSize = right - middle;

	int leftArr[leftArrSize];
	int rightArr[rightArrSize];

	int firstLeftIndex = left;
	int firstRightIndex = middle + 1;

	for (int i = 0; i < leftArrSize; i++) {
		leftArr[i] = array[left + i];
	}

	for (int i = 0; i < rightArrSize; i++) {
		rightArr[i] = array[firstRightIndex + i];
	}

	int i = 0;
	int j = 0;
	int index = firstLeftIndex;
	while (i < middle - left + 1 && j < right - middle) {
		if (leftArr[i] <= rightArr[j]) {
			array[index] = leftArr[i];
			i++;
		} else {
			array[index] = rightArr[j];
			j++;
		}
		index++;
	}

	while (i < middle - left + 1) {
		array[index] = leftArr[i];
		i++;
		index++;
	}

	while (j < right - middle) {
		array[index] = rightArr[j];
		j++;
		index++;
	}
}