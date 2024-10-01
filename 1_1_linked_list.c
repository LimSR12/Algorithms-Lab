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
	scanf("%d", &numOperations); // 연산의 개수

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

//노드 생성 및 초기화
Node* createNode(Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

// 리스트 생성 및 초기화
List* createLinkedList() {
	List* list = (List*)malloc(sizeof(List));
	list->current = NULL;
	list->header = NULL;
	list->trailer = NULL;

	list->numOfData = 0;
	return list;
}

// list의 순위 r에 원소 e를 추가한다.	
// r 만큼 loop 돌며 current 위치를 next로 옮겨준 뒤 loop 종료되고 나서 해당 위치에 삽입해주자
void add(List* list, int r, char e) {
	Node* newNode = createNode(e);

	if (r < 1 || r > list->numOfData + 1) { // 유효하지 않은 순위
		printf("invalid position\n");
		free(newNode);
		return;
	}

	if (list->header == NULL) { // header -> NULL (리스트가 비어있음)
		list->header = newNode;
		list->trailer = newNode;
	}
	else if (r == 1) { // 리스트가 비어있지 않고 맨 앞에 삽입

		newNode->next = list->header;
		list->header->prev = newNode;
		list->header = newNode;
	}
	else if (r > list->numOfData) { // 리스트가 비어있지 않고 맨 마지막에 삽입
		newNode->prev = list->trailer;
		list->trailer->next = newNode;
		list->trailer = newNode;
	}
	else { // 중간에 위치 찾아들어가야함
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

// list의 순위 r에 위치한 원소를 삭제한다.
Data delete(List* list, int r) {
	if (list->header == NULL || r < 1 || r > list->numOfData) { // 리스트가 비어있거나 잘못된 위치일 때
		printf("invalid position\n");
		return '\0';
	}

	Node* current = list->header;

	if (r == 1) { // 첫 번째 노드를 삭제하는 경우
		list->header = current->next;
		if (list->header != NULL) {
			list->header->prev = NULL;
		}
		else {
			list->trailer = NULL; // 리스트에 하나만 있는 경우
		}
	}
	else if (r == list->numOfData) { // 마지막 노드를 삭제하는 경우
		current = list->trailer;
		list->trailer = current->prev;
		if (list->trailer != NULL) {
			list->trailer->next = NULL;
		}
		else {
			list->header = NULL; // 리스트에 하나만 있는 경우
		}
	}
	else { // 중간의 노드를 삭제하는 경우
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

// list의 순위 r에 위치한 원소를 반환한다.
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


// list의 모든 원소를 저장 순위대로 공백없이 출력한다. 
void print(List* list) {
	Node* current = list->header;

	while (current != NULL) {
		printf("%c", current->elem);
		current = current->next;
	}
	printf("\n");
	return;
}


