#pragma warning(disable:4996)
#include <stdio.h>

#define HEAP_SIZE 100

int Heap[HEAP_SIZE];  // �� �迭
int n = 0;  // ���� �� �׸� �� ���� = �� ũ��

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
    if (i == 1) return;  // ��Ʈ�� �����ϸ� ����
    int parent = i / 2;
    if (Heap[i] > Heap[parent]) {  // �θ𺸴� ũ�� ��ȯ
        int temp = Heap[i];
        Heap[i] = Heap[parent];
        Heap[parent] = temp;
        upHeap(parent);  // ��������� �θ� ���� �̵�
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
        downHeap(greater);  // ��������� ����������
    }
}

void insertItem(int key) {
    n++; // ù ������ n+1����
    Heap[n] = key;
    upHeap(n);  // ���� ������ �����ϵ���
    printf("0\n");
}

int removeMax() {
    int max = Heap[1];  // ��Ʈ�� �ִ� �ִ밪
    Heap[1] = Heap[n];  // ������ ���Ҹ� ��Ʈ�� �̵�
    n--;
    downHeap(1);  // ���� ������ �����ϵ���
    return max;
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", Heap[i]);
    }
    printf("\n");
}