/*
* �պ�����
*/

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0

typedef int Data;

typedef struct _node {
	Data data;
	struct _node* next;
} Node;

typedef struct _linkedlist {
	//int numOfData;
	Node* head;
	//Node* tail;
	Node* cur; // ���Ḯ��Ʈ �� ���� ����Ű�� ��
} List;

void printList(List* list);
int isEmpty(List* list);
List* makeList();
void appendNode(List* list, Node* node);
int moveToNextNode(List* list);


void mergeSort(List** L);
List* merge(List* L1, List* L2);
void partition(List* list, int k, List** L1, List** L2);


// n���� ���� ����(�ߺ� ����)�� �Է¹޾� �����ϴ� ���α׷��� �ۼ��Ͻÿ�. 
// ������ ���Ͽ��Ḯ��Ʈ�� �̿��Ͽ� �պ� ������ �����Ͽ� ����Ѵ�.
int main() {

	List* list = makeList();

	int n, data;

	scanf("%d", &n);
		
	// n���� ��� �����Ͽ� ����
	for (int i = 0; i < n; i++) {
		scanf("%d", &data);
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->data = data;
		newNode->next = NULL;

		appendNode(list, newNode);
	}

	mergeSort(&list);

	printList(list);

	free(list);
	return 0;
}

// ####################################### List functions #######################################

int isEmpty(List* list) {
	if (list->head->next == NULL) return TRUE;
	else return FALSE;
	return;
}

List* makeList() {
	List* list = (List*)malloc(sizeof(List));

	// ������ ����Ʈ�� head ���� NULL ����Ŵ
	list->head = (Node*)malloc(sizeof(Node));
	list->head->next = NULL;
	// ���� �����ʹ� ���� ���� -> head���� -1 �ϴ� �־��
	list->head->data = -1;

	list->cur = list->head;

	return list;
}

// �ϴ� �ܹ��� ���Ḯ��Ʈ�� ����   ->   �պ� ���� ���� �����ϴ°� ��ǥ
// �׷��� �׳� append ��ĸ� ���
void appendNode(List* list, Node* node) {
	if (list->head->next == NULL) { // ����Ʈ�� ����ִٸ�  ( head -> NULL �̸� )
		list->head->next = node;
		node->next = NULL;
	}
	else { // ����Ʈ�� ���� ����ִٸ�
		list->cur = list->head;
		while (moveToNextNode(list)) { // ���� Ȯ���� ���->next �� NULL�� ���ö����� ������
			//list->cur = list->cur->next;
		}
		list->cur->next = node;
		node->next = NULL;
	}
	return;
}

// ���� ��尡 �����ϸ� 1, �������� ������ 0 ��ȯ
int moveToNextNode(List* list) {
	//list->cur->next = list->head->next;
	if (list->cur->next == NULL) {
		return FALSE;
	}
	list->cur = list->cur->next;
	return TRUE;
}

void printList(List* list) {
	list->cur = list->head;
	while (moveToNextNode(list)) {
		printf("%d ", list->cur->data);
	}
	printf("\n");
	return;
}

// ####################################### Merge Sort functions #######################################

void mergeSort(List** L) {
	// ����Ʈ�� ����ְų�, ������ ������ 1�̸� �׳� return
	if ((*L)->head->next == NULL || (*L)->head->next->next == NULL) return;

	// ����Ʈ�� ���� Ȯ���ؼ� k�� ����
	int k = 0;
	Node* cur = (*L)->head->next;
	while (cur != NULL) {
		cur = cur->next;
		k++;
	}

	// ��������� partition(), merge() �Լ� ȣ��
	List* L1 = makeList();
	List* L2 = makeList();

	partition(*L, k / 2, &L1, &L2); // L1�� L2���� ������ �ɰ����� �����

	//����
	mergeSort(&L1);
	mergeSort(&L2);

	//����
	*L = merge(L1, L2);

	return;
};

// partition�� ���� ���� L1�� L2�� ����
List* merge(List* L1, List* L2) {
	List* sortedList = makeList();

	// L1�� L2 Ȯ���ϸ� ����, ����  ->  L2�� L1���� ���ų� ũ��
	Node* cur1 = L1->head->next;
	Node* cur2 = L2->head->next;

	Node* sortedCur = sortedList->head;

	while (cur1 != NULL && cur2 != NULL) { // cur1�� cur2�� �� �� NULL�� �ƴ� ���� �ݺ��Ұǵ�,
		if (cur1->data <= cur2->data) { // cur1�� �� ������ sortedCur  ->   cur1 �� �ǵ���
			sortedCur->next = cur1;
			cur1 = cur1->next;
		}
		else { // cur2�� �� ������ sortedCur  ->   cur2 �� �ǵ���
			sortedCur->next = cur2;
			cur2 = cur2->next;
		}
		// cur1�� cur2 �ٱ��ؼ� �ϳ� �־����� ���� �ݺ����� 
		sortedCur = sortedCur->next;
	}
	
	// ����Ʈ�� Ȧ�������� �� �� �ϳ��� NULL�� �ƴ� �� �ִ�.
	while (cur1 != NULL) {
		sortedCur->next = cur1;
		cur1 = cur1->next;
		sortedCur = sortedCur->next;
	}
	while (cur2 != NULL) {
		sortedCur->next = cur2;
		cur2 = cur2->next;
		sortedCur = sortedCur->next;
	}

	return sortedList;
};


// ���Ͽ��Ḯ��Ʈ L�� ���� ���� k�� ���޹޾� L�� ũ�Ⱑ k�̰� |L| - k�� �� ���� �θ���Ʈ L1�� L2�� �����Ͽ�(L1, L2)�� ��ȯ.
// ���⼭ | L | ��L�� ũ��.
// ���� �ÿ��� �־��� L ���� �ܿ� O(1) ������ �߰� ��밡��.
// ==> ���������ͷ� ���޹޾� ����Ʈ ����
void partition(List* list, int k, List** L1, List** L2) {	

	Node* cur = list->head->next; // cur �� list�� ù��° ��� ����Ŵ

	(*L1)->head->next = list->head->next;

	// k ��° ������ �̵�
	for (int i = 1; i < k && cur != NULL; i++) {
		cur = cur->next;
	}

	if (cur != NULL) {
		(*L2)->head->next = cur->next; // L2�� k+1 ��° ������
		cur->next = NULL;
	}
	else {
		(*L2)->head->next = NULL;
	}
}

/*
	* idea
	* ������ �ΰ��� �����
	* �ϳ��� ��ĭ��(Node* slow) �ϳ��� ��ĭ��(Node* fast)
	* ��ĭ�� ���� �����Ͱ� �������� �����ϸ� ��ĭ ���� ������ ��ġ�� �߾��ϰžƴϾ�
	* �׷� �� �����Ͱ� ����Ű�� ��尡 L1�� ������ ���. �� �ٷ� ���� ��尡 L2�� ù��° ���
	*
	* List* list1 = (List*)malloc(sizeof(List));
	* List* list2 = (List*)malloc(sizeof(List));
	*
	* list1->head->next = list->head->next;
	* list2->head->next = list->slow->next;
	* �ٵ� �̷��� O(1) ������ ����ϴ°� �³�?
	*/