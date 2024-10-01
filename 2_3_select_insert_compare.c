#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#pragma warning(disable:4996)

void selectSort(int* arr_A, int n);
void insertSort(int* arr_B, int n);

int main() {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	srand(time(NULL));

	int n = 100000; // 초기 n
	int difference = 100000; // 등차

	for (int i = 0; i < 10; i++) {
		printf("n = %d\n", n);

		// 배열 동적 할당
		int* arr_A = (int*)malloc(sizeof(int) * n); 
		int* arr_B = (int*)malloc(sizeof(int) * n);

		// 배열 초기화
		for (int index = 0; index < n; index++) {
			arr_A[index] = arr_B[index] = rand();
			// arr_A[index] = arr_B[index] = index;
			// arr_A[index] = arr_B[index] = n - index;
		}
		
		// 배열 사전 정렬
		//insertSort(arr_A, n);
		//insertSort(arr_B, n);

		QueryPerformanceFrequency(&ticksPerSec);

		QueryPerformanceCounter(&start); // 시간 측정 시작

		selectSort(arr_A, n);

		QueryPerformanceCounter(&end); // 시간 측정 종료

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.7f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);


		QueryPerformanceCounter(&start); // 시간 측정 시작

		insertSort(arr_B, n);

		QueryPerformanceCounter(&end); // 시간 측정 종료

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.7f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		free(arr_A);
		free(arr_B);

		n += difference;
	}

	return 0;
}

// 선택 정렬
void selectSort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		int minLoc = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minLoc]) {
				minLoc = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[minLoc];
		arr[minLoc] = tmp;
	}
};

// 삽입 정렬
void insertSort(int* arr, int n) {
	for (int i = 1; i < n; i++) {
		int save = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > save) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = save;
	}
};
