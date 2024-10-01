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
		int maxIndex = 0; // arr[1] ~ arr[n-i-1] �߿��� arr[0]�� ���������� �����ؼ� max value ã��

		for (int j = 1; j < n - i; j++) {
			if (arr[j] > arr[maxIndex]) {
				maxIndex = j; // ã������ �ش� ��ġ(index) ����
			}
		}

		int tmp = arr[maxIndex];
		arr[maxIndex] = arr[n - 1 - i]; // n-1 ���� i ���� ( �ش� ���� ���� ���� ���� ������ �ε��� )
		arr[n - i - 1] = tmp;

		// ***
		printf("%dȸ�� ��� : ",i+1);
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