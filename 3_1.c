#pragma warning(disable:4996)
#include <stdio.h>

#define HEAP_SIZE 100

int Heap[HEAP_SIZE];  // 힙 배열
int n = 0;  // 현재 총 항목 수 유지 = 힙 크기

void upHeap(int i);
void downHeap(int i);
void insertItem(int key);
int removeMax();
void printHeap();

int main() {
    char command;
    int key;

    while (1) {
        scanf(" %c", &command);
        if (command == 'i') {
            scanf("%d", &key);
            insertItem(key);
        }
        else if (command == 'd') {
            if (n == 0) {
                printf("Heap is empty\n");
            }
            else {
                printf("%d\n", removeMax());
            }
        }
        else if (command == 'p') {
            if (n == 0) {
                printf("Heap is empty\n");
            }
            else {
                printHeap();
            }
        }
        else if (command == 'q') {
            break;
        }
    }

    return 0;
}

void upHeap(int i) {
    if (i == 1) return;  // 루트에 도달하면 종료
    int parent = i / 2;
    if (Heap[i] > Heap[parent]) {  // 부모보다 크면 교환
        int temp = Heap[i];
        Heap[i] = Heap[parent];
        Heap[parent] = temp;
        upHeap(parent);  // 재귀적으로 부모 노드로 이동
    }
}

void downHeap(int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int greater = i;

    if (left <= n && Heap[left] > Heap[greater]) {
        greater = left;
    }
    if (right <= n && Heap[right] > Heap[greater]) {
        greater = right;
    }
    if (greater != i) {
        int temp = Heap[i];
        Heap[i] = Heap[greater];
        Heap[greater] = temp;
        downHeap(greater);  // 재귀적으로 내려가도록
    }
}

void insertItem(int key) {
    n++; // 첫 삽입은 n+1부터
    Heap[n] = key;
    upHeap(n);  // 힙의 순서를 유지하도록
    printf("0\n");
}

int removeMax() {
    int max = Heap[1];  // 루트에 있는 최대값
    Heap[1] = Heap[n];  // 마지막 원소를 루트로 이동
    n--;
    downHeap(1);  // 힙의 순서를 유지하도록
    return max;
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", Heap[i]);
    }
    printf("\n");
}