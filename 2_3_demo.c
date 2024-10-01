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

	// 배열 생성
	int n;
	scanf("%d", &n);

	int* arr_A = (int*)malloc(sizeof(int) * n);
	int* arr_B = (int*)malloc(sizeof(int) * n);
	
	for (int i = 0; i < n; i++) { // 배열 초기화
		arr_B[i] = arr_A[i] = rand();
	}

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);

	// 시간 측정 시작

	// 선택정렬
	selectSort(arr_A, n);

	// 시간 측정 끝

	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.7fsec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	
	//****************************************************************************************

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);

	// 시간 측정 시작
	// 삽입정렬

	insertSort(arr_B, n);

	// 시간 측정 종료

	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.7fsec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	free(arr_A);
	free(arr_B);

	return 0;
}

// 교재 코드
void selectSort(int* arr_A, int n) {
	for (int i = 0; i < n - 1; i++) {
		int minLoc = i;
		for (int j = i + 1; j < n; j++) {
			if (arr_A[j] < arr_A[minLoc]) {
				minLoc = j;
			}
		}
		// swap
		int tmp = arr_A[i];
		arr_A[i] = arr_A[minLoc];
		arr_A[minLoc] = tmp;
	}
	/*for (int i = 0; i < n; i++) {
		printf("%d ", arr_A[i]);
	}
	printf("\n");*/
};

// 내 코드
//void selectSort(int* arr_A, int n) {
//	for (int i = 0; i < n - 1; i++) {
//		int maxIndex = 0;
//		for (int j = 1; j < n - i; j++) {
//			if (arr_A[j] > arr_A[maxIndex]) {
//				maxIndex = j;
//			}
//		}
//		// swap
//		int tmp = arr_A[maxIndex];
//		arr_A[maxIndex] = arr_A[n - i - 1];
//		arr_A[n - i - 1] = tmp;
//	}
//	/*for (int i = 0; i < n; i++) {
//		printf("%d ", arr_A[i]);
//	}*/
//};

// 교재 코드
void insertSort(int* arr, int n) {
	for (int i = 1; i < n; i++) { // i 는 1부터 n-1까지
		int save = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > save) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = save;
	}

	/*for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");*/
};

//내 코드
//void insertSort(int* arr_B, int n) {
//	for (int i = 1; i < n; i++) { // i 는 1부터 n-1까지
//		for (int j = i; j > 0; j--) { // j 는 i부터 1까지
//			if (arr_B[j] > arr_B[j - 1]) {
//				break;
//			}
//			else {
//				int temp = arr_B[j];
//				arr_B[j] = arr_B[j - 1];
//				arr_B[j - 1] = temp;
//			}
//		}
//	}
//
//	for (int i = 1; i < n; i++) {
//		int key = arr_B[i];
//		int j;
//
//		// for 문을 이용하여 요소를 오른쪽으로 이동
//		for (j = i - 1; j >= 0 && arr_B[j] > key; j--) {
//			arr_B[j + 1] = arr_B[j];
//		}
//		arr_B[j + 1] = key;
//	}
//
//	for (int i = 0; i < n; i++) {
//		printf("%d ", arr_B[i]);
//	}
//	printf("\n");
//};
