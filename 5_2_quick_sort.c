#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct _coord {
	int a;
	int b;
}Co; 

void inPlaceQuickSort(int* arr, int l, int r);
Co inPlacePartition(int* arr, int l, int r, int k);
int findPivot(int* arr, int l, int r);
void swap(int* arr, int l, int r);
void printArr(int* arr, int size);

int main() {
	int n;
	int pivot;
	srand(time(NULL));

	scanf("%d", &n);
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	inPlaceQuickSort(arr, 0, n-1);
	printArr(arr, n);

	free(arr); // 메모리 해제
	return 0;
}

void inPlaceQuickSort(int* arr, int l, int r) {
	if (l >= r) {
		return;
	}
	int pivot = findPivot(arr, l, r);

	Co result = inPlacePartition(arr, l, r, pivot);

	inPlaceQuickSort(arr, l, result.a - 1);
	inPlaceQuickSort(arr, result.b + 1, r);
	return;
}

Co inPlacePartition(int* arr, int l, int r, int k) {

	Co res; // 결과 담아서 반환할 구조체

	int pivotVal = arr[k];
	swap(arr, r, k);

	int i = l;
	int j = r - 1;

	while (i <= j) {
		while (i <= j && arr[i] <= pivotVal)i++;
		while (i <= j && arr[j] >= pivotVal)j--;
		if (i < j) {
			swap(arr, i, j);
		}
	}
	swap(arr, i, r);

	res.a = i;
	res.b = i;
	return res;
}

int findPivot(int* arr, int l, int r) {
	int pivot = l + rand() % (r - l + 1);
	return pivot;
}

void swap(int* arr, int l, int r) {
	int temp = arr[l];
	arr[l] = arr[r];
	arr[r] = temp;
	return;
}

void printArr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	return;
}