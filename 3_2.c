#pragma warning(disable:4996)
#include <stdio.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];  // 힙 배열
int n = 0;  // 힙의 크기

void downHeap(int i);
void buildHeap();
void rBuildHeap(int i);
void printHeap();

int main() {
    int keyCount;

    // 키의 개수 입력
    scanf("%d", &keyCount);
    n = keyCount;

    // 키들을 입력받음
    for (int i = 1; i <= n; i++) {
        scanf("%d", &heap[i]);
    }

    // 상향식 힙 생성
    buildHeap();

    // 힙 출력
    printHeap();

    return 0;
}

void downHeap(int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int greater = i;

    if (left <= n && heap[left] > heap[greater]) {
        greater = left;
    }
    if (right <= n && heap[right] > heap[greater]) {
        greater = right;
    }
    if (greater != i) {
        int temp = heap[i];
        heap[i] = heap[greater];
        heap[greater] = temp;
        downHeap(greater);
    }
    return;
}

void buildHeap() {
    for (int i = n / 2; i >= 1; i--) {
        downHeap(i);  // 힙을 재구성 (최하위 부모부터 시작)
    }
    return;
}

void rBuildHeap(int i) {
    if (i > n) return;  // 배열 범위를 넘어가면 종료

    rBuildHeap(2 * i);      // 왼쪽 부트리 힙 생성
    rBuildHeap(2 * i + 1);  // 오른쪽 부트리 힙 생성
    downHeap(i);            // 현재 부트리 루트를 힙으로 정렬
    return;
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
    return;
}