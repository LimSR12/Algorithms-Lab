#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef char Data;

typedef struct _node {
	Data elem;
	struct _node* prev;
	struct _node* next;
} Node;

typedef struct _linkedlist {
	int numOfData;
	Node* current;
	Node* header;
	Node* trailer;
} List;

Node* createNode(Data data);
List* createLinkedList();
void add(List* list, int r, char e);
Data delete(List* list, int r);
Data get(List* list, int r);
void print(List* list);

/*
input

9
A 1 D
A 2 a
A 3 y
D 1
P
G 3
A 1 S
P
G 3
*/

int main() {
	List* list = createLinkedList();

	int numOperations;
	scanf("%d", &numOperations); // ������ ����

	for (int i = 0; i < numOperations; i++) {
		char operation;
		scanf(" %c", &operation);

		if (operation == 'A') { // add
			int r;
			char e;
			scanf("%d %c", &r, &e);
			add(list, r, e);
		}
		else if (operation == 'D') { // delete
			int r;
			scanf("%d", &r);
			delete(list, r);
		}
		else if (operation == 'G') { // get
			int r;
			scanf("%d", &r);
			char result = get(list, r);
			if (result != '\0') {
				printf("%c\n", result);
			}
		}
		else if (operation == 'P') { // print
			print(list);
		}
	}

	free(list);
	return 0;
}

//��� ���� �� �ʱ�ȭ
Node* createNode(Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

// ����Ʈ ���� �� �ʱ�ȭ
List* createLinkedList() {
	List* list = (List*)malloc(sizeof(List));
	list->current = NULL;
	list->header = NULL;
	list->trailer = NULL;

	list->numOfData = 0;
	return list;
}

// list�� ���� r�� ���� e�� �߰��Ѵ�.	
// r ��ŭ loop ���� current ��ġ�� next�� �Ű��� �� loop ����ǰ� ���� �ش� ��ġ�� ����������
void add(List* list, int r, char e) {
	Node* newNode = createNode(e);

	if (r < 1 || r > list->numOfData + 1) { // ��ȿ���� ���� ����
		printf("invalid position\n");
		free(newNode);
		return;
	}

	if (list->header == NULL) { // header -> NULL (����Ʈ�� �������)
		list->header = newNode;
		list->trailer = newNode;
	}
	else if (r == 1) { // ����Ʈ�� ������� �ʰ� �� �տ� ����

		newNode->next = list->header;
		list->header->prev = newNode;
		list->header = newNode;
	}
	else if (r > list->numOfData) { // ����Ʈ�� ������� �ʰ� �� �������� ����
		newNode->prev = list->trailer;
		list->trailer->next = newNode;
		list->trailer = newNode;
	}
	else { // �߰��� ��ġ ã�Ƶ�����
		Node* current = list->header;
		for (int i = 1; i < r - 1; i++) {
			current = current->next;
		}
		newNode->next = current->next;
		newNode->prev = current;
		current->next->prev = newNode;
		current->next = newNode;
	}
	list->numOfData++;
	return;
}

// list�� ���� r�� ��ġ�� ���Ҹ� �����Ѵ�.
Data delete(List* list, int r) {
	if (list->header == NULL || r < 1 || r > list->numOfData) { // ����Ʈ�� ����ְų� �߸��� ��ġ�� ��
		printf("invalid position\n");
		return '\0';
	}

	Node* current = list->header;

	if (r == 1) { // ù ��° ��带 �����ϴ� ���
		list->header = current->next;
		if (list->header != NULL) {
			list->header->prev = NULL;
		}
		else {
			list->trailer = NULL; // ����Ʈ�� �ϳ��� �ִ� ���
		}
	}
	else if (r == list->numOfData) { // ������ ��带 �����ϴ� ���
		current = list->trailer;
		list->trailer = current->prev;
		if (list->trailer != NULL) {
			list->trailer->next = NULL;
		}
		else {
			list->header = NULL; // ����Ʈ�� �ϳ��� �ִ� ���
		}
	}
	else { // �߰��� ��带 �����ϴ� ���
		for (int i = 1; i < r; i++) {
			current = current->next;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	Data returnData = current;
	free(current);
	list->numOfData--;
	return returnData;
}

// list�� ���� r�� ��ġ�� ���Ҹ� ��ȯ�Ѵ�.
Data get(List* list, int r) {
	if (r < 1 || r > list->numOfData) {
		printf("invalid position\n");
		return '\0';
	}
	Node* current = list->header;
	for (int i = 1; i < r; i++) {
		current = current->next;
	}
	return current->elem;
}


// list�� ��� ���Ҹ� ���� ������� ������� ����Ѵ�. 
void print(List* list) {
	Node* current = list->header;

	while (current != NULL) {
		printf("%c", current->elem);
		current = current->next;
	}
	printf("\n");
	return;
}


