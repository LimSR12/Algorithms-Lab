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

	// �迭 ����
	int n;
	scanf("%d", &n);

	int* arr_A = (int*)malloc(sizeof(int) * n);
	int* arr_B = (int*)malloc(sizeof(int) * n);
	
	for (int i = 0; i < n; i++) { // �迭 �ʱ�ȭ
		arr_B[i] = arr_A[i] = rand();
	}

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);

	// �ð� ���� ����

	// ��������
	selectSort(arr_A, n);

	// �ð� ���� ��

	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.7fsec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	
	//****************************************************************************************

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);

	// �ð� ���� ����
	// ��������

	insertSort(arr_B, n);

	// �ð� ���� ����

	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.7fsec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	free(arr_A);
	free(arr_B);

	return 0;
}

// ���� �ڵ�
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

// �� �ڵ�
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

// ���� �ڵ�
void insertSort(int* arr, int n) {
	for (int i = 1; i < n; i++) { // i �� 1���� n-1����
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

//�� �ڵ�
//void insertSort(int* arr_B, int n) {
//	for (int i = 1; i < n; i++) { // i �� 1���� n-1����
//		for (int j = i; j > 0; j--) { // j �� i���� 1����
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
//		// for ���� �̿��Ͽ� ��Ҹ� ���������� �̵�
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
