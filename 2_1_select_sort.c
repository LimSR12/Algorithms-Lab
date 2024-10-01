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
	
	int n;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < n - 1; i++) {
		int maxIndex = 0; // arr[1] ~ arr[n-i-1] 중에서 arr[0]을 기준점으로 시작해서 max value 찾자

		for (int j = 1; j < n - i; j++) {
			if (arr[j] > arr[maxIndex]) {
				maxIndex = j; // 찾았으면 해당 위치(index) 저장
			}
		}

		int tmp = arr[maxIndex];
		arr[maxIndex] = arr[n - 1 - i]; // n-1 보다 i 작은 ( 해당 루프 도는 순간 가장 마지막 인덱스 )
		arr[n - i - 1] = tmp;

		// ***
		printf("%d회전 결과 : ",i+1);
		for (int i = 0; i < n; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
	}



	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	free(arr);

	return 0;
}