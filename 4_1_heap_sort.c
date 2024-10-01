#pragma warning(disable:4996)
#include <stdio.h>

int heap[100];
int n;

void inPlaceHeapSort();
void printArray();

void downHeap(int i, int last);
void buildHeap();

int main() {

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
        scanf("%d", &heap[i]); 
	}

    inPlaceHeapSort();

    printArray();

	return 0;
}

// inPlaceHeapSort �Լ�: �� ������ �����ϴ� �Լ�
void inPlaceHeapSort() {
    buildHeap();
    
    for (int i = n; i >= 2; i--) {
        // ��Ʈ(�ִ밪)�� ������ �׸��� ��ȯ
        int temp = heap[1];
        heap[1] = heap[i];
        heap[i] = temp;

        // ���� ���� ���� �ִ��� �Ӽ� ����
        downHeap(1, i-1);
    }
}

void downHeap(int i, int last) {/*
    printf("i = %d, last = %d\n", i, last);
    printArray();*/
    // i�� ������ i�� �ڸ��� ã���ٰž�
    // i�� �׻� 1�� ��? ������ -> ��Ʈ�� last �ٲ� -> ok ������
    
    int left = 2 * i; // left child
    int right = 2 * i + 1; // right child

    int greater = i; 
    // �ִ밪�� �����Ұǵ�, left�� right�� �� ũ�� ���� �� �ٽ� downHeap (���)
    // �ִ밪 ���ŵ��� �ʰ� i �״�� �������� return

   /* if (left <= last && heap[left] > heap[i]) {
        greater = left;
    }
    if (right <= last && heap[right] > heap[i]) {
        greater = right;
    }*/

    if (left <= last && heap[left] > heap[greater]) {
        greater = left;
    }
    if (right <= last && heap[right] > heap[greater]) {
        greater = right;
    }


    if (greater != i) {
        //swap
        int temp = heap[i];
        heap[i] = heap[greater];
        heap[greater] = temp;
        downHeap(greater, last);
    }
    return;
}

void buildHeap() {
    //int ch = 1;
    for (int i = n / 2; i >= 1; i--) {
        //printf("buildHeap call : %d\n", ch);
        //ch++;
        downHeap(i, n);  // ���� �籸�� (������ �θ���� ����)
        //printf("---------buildHeap end---------\n");
    }
    return;
}


// printArray �Լ�: ���ĵ� �迭�� ����ϴ� �Լ�
void printArray() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}
