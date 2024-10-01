#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

/*
input

8
8 31 48 73 3 65 20 29
*/

int main() {
	int length;
	scanf("%d", &length);

	int* arr = (int*)malloc(sizeof(int) * length); // 배열 동적할당

	for (int i = 0; i < length; i++) {
		scanf("%d", &arr[i]);
	}

	// 삽입정렬
	for (int i = 1; i < length; i++) {
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) {
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
			else {
				continue;
			}
		}
	}

	for (int i = 0; i < length; i++) {
		printf("%d ", arr[i]);
	}

	free(arr);

	return 0;
}