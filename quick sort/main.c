#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int A[8];

void printArr(int A[8]) {
  for (int i = 0; i < 8; i++) {
	printf("%d ", A[i]);
  }
  printf("\n");
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int Partition(int A[8], int start, int end) {
  int pivot = A[end];
  int pIndex = start;
  for (int i = start; i < end; i++) {
	if (A[i] <= pivot) {
	  swap(A+i, A+pIndex);
	  pIndex++;
	}
  }
  swap(A+pIndex, A+end);

  printArr(A);
  
  return pIndex;
}

void QuickSort(int A[8], int start, int end) {
  if (start < end) {
	int pIndex = Partition(A, start, end);
	QuickSort(A, start, pIndex - 1);
	QuickSort(A, pIndex + 1, end);
  } else {
	return;
  }
}

int main() {
  int arr[8] = {2, 3, 8, 1, 5, 4, 7, 6};

  memcpy(A, arr, sizeof(int)*8);

  printArr(A);

  QuickSort(A, 0, 7);

  printArr(A);
}
