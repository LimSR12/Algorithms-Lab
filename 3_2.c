#pragma warning(disable:4996)
#include <stdio.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];  // �� �迭
int n = 0;  // ���� ũ��

void downHeap(int i);
void buildHeap();
void rBuildHeap(int i);
void printHeap();

int main() {
    int keyCount;

    // Ű�� ���� �Է�
    scanf("%d", &keyCount);
    n = keyCount;

    // Ű���� �Է¹���
    for (int i = 1; i <= n; i++) {
        scanf("%d", &heap[i]);
    }

    // ����� �� ����
    buildHeap();

    // �� ���
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
        downHeap(i);  // ���� �籸�� (������ �θ���� ����)
    }
    return;
}

void rBuildHeap(int i) {
    if (i > n) return;  // �迭 ������ �Ѿ�� ����

    rBuildHeap(2 * i);      // ���� ��Ʈ�� �� ����
    rBuildHeap(2 * i + 1);  // ������ ��Ʈ�� �� ����
    downHeap(i);            // ���� ��Ʈ�� ��Ʈ�� ������ ����
    return;
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
    return;
}