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

// inPlaceHeapSort 함수: 힙 정렬을 수행하는 함수
void inPlaceHeapSort() {
    buildHeap();
    
    for (int i = n; i >= 2; i--) {
        // 루트(최대값)과 마지막 항목을 교환
        int temp = heap[1];
        heap[1] = heap[i];
        heap[i] = temp;

        // 남은 힙에 대해 최대힙 속성 유지
        downHeap(1, i-1);
    }
}

void downHeap(int i, int last) {/*
    printf("i = %d, last = %d\n", i, last);
    printArray();*/
    // i가 들어오면 i의 자리를 찾아줄거야
    // i를 항상 1로 왜? 힙정렬 -> 루트랑 last 바꿔 -> ok 내려가
    
    int left = 2 * i; // left child
    int right = 2 * i + 1; // right child

    int greater = i; 
    // 최대값을 저장할건데, left나 right가 더 크면 갱신 후 다시 downHeap (재귀)
    // 최대값 갱신되지 않고 i 그대로 내려오면 return

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
        downHeap(i, n);  // 힙을 재구성 (최하위 부모부터 시작)
        //printf("---------buildHeap end---------\n");
    }
    return;
}


// printArray 함수: 정렬된 배열을 출력하는 함수
void printArray() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}
