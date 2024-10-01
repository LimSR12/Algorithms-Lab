/*
* 합병정렬
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
	Node* cur; // 연결리스트 내 현재 가리키는 곳
} List;

void printList(List* list);
int isEmpty(List* list);
List* makeList();
void appendNode(List* list, Node* node);
int moveToNextNode(List* list);


void mergeSort(List** L);
List* merge(List* L1, List* L2);
void partition(List* list, int k, List** L1, List** L2);


// n개의 양의 정수(중복 가능)를 입력받아 정렬하는 프로그램을 작성하시오. 
// 정렬은 단일연결리스트를 이용하여 합병 정렬을 구현하여 사용한다.
int main() {

	List* list = makeList();

	int n, data;

	scanf("%d", &n);
		
	// n개의 노드 생성하여 연결
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

	// 생성된 리스트의 head 노드는 NULL 가리킴
	list->head = (Node*)malloc(sizeof(Node));
	list->head->next = NULL;
	// 삽입 데이터는 양의 정수 -> head에는 -1 일단 넣어둠
	list->head->data = -1;

	list->cur = list->head;

	return list;
}

// 일단 단방향 연결리스트로 구현   ->   합병 정렬 통해 정렬하는게 목표
// 그래서 그냥 append 방식만 고려
void appendNode(List* list, Node* node) {
	if (list->head->next == NULL) { // 리스트가 비어있다면  ( head -> NULL 이면 )
		list->head->next = node;
		node->next = NULL;
	}
	else { // 리스트에 뭔가 들어있다면
		list->cur = list->head;
		while (moveToNextNode(list)) { // 현재 확인한 노드->next 가 NULL이 나올때까지 움직임
			//list->cur = list->cur->next;
		}
		list->cur->next = node;
		node->next = NULL;
	}
	return;
}

// 다음 노드가 존재하면 1, 존재하지 않으면 0 반환
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
	// 리스트가 비어있거나, 원소의 개수가 1이면 그냥 return
	if ((*L)->head->next == NULL || (*L)->head->next->next == NULL) return;

	// 리스트의 길이 확인해서 k에 저장
	int k = 0;
	Node* cur = (*L)->head->next;
	while (cur != NULL) {
		cur = cur->next;
		k++;
	}

	// 재귀적으로 partition(), merge() 함수 호출
	List* L1 = makeList();
	List* L2 = makeList();

	partition(*L, k / 2, &L1, &L2); // L1과 L2에는 반으로 쪼개져서 저장됨

	//정렬
	mergeSort(&L1);
	mergeSort(&L2);

	//병합
	*L = merge(L1, L2);

	return;
};

// partition을 통해 나눈 L1과 L2를 병합
List* merge(List* L1, List* L2) {
	List* sortedList = makeList();

	// L1과 L2 확인하며 정렬, 병합  ->  L2는 L1보다 같거나 크다
	Node* cur1 = L1->head->next;
	Node* cur2 = L2->head->next;

	Node* sortedCur = sortedList->head;

	while (cur1 != NULL && cur2 != NULL) { // cur1과 cur2가 둘 다 NULL이 아닌 동안 반복할건데,
		if (cur1->data <= cur2->data) { // cur1이 더 작으면 sortedCur  ->   cur1 이 되도록
			sortedCur->next = cur1;
			cur1 = cur1->next;
		}
		else { // cur2가 더 작으면 sortedCur  ->   cur2 가 되도록
			sortedCur->next = cur2;
			cur2 = cur2->next;
		}
		// cur1과 cur2 바교해서 하나 넣었으니 다음 반복으로 
		sortedCur = sortedCur->next;
	}
	
	// 리스트가 홀수개여서 둘 중 하나가 NULL이 아닐 수 있다.
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


// 단일연결리스트 L과 양의 정수 k를 전달받아 L을 크기가 k이고 |L| - k인 두 개의 부리스트 L1과 L2로 분할하여(L1, L2)를 반환.
// 여기서 | L | 은L의 크기.
// 분할 시에도 주어진 L 공간 외에 O(1) 공간만 추가 사용가능.
// ==> 더블포인터로 전달받아 리스트 분할
void partition(List* list, int k, List** L1, List** L2) {	

	Node* cur = list->head->next; // cur 는 list의 첫번째 노드 가리킴

	(*L1)->head->next = list->head->next;

	// k 번째 노드까지 이동
	for (int i = 1; i < k && cur != NULL; i++) {
		cur = cur->next;
	}

	if (cur != NULL) {
		(*L2)->head->next = cur->next; // L2는 k+1 번째 노드부터
		cur->next = NULL;
	}
	else {
		(*L2)->head->next = NULL;
	}
}

/*
	* idea
	* 포인터 두개를 만들어
	* 하나는 한칸씩(Node* slow) 하나는 두칸씩(Node* fast)
	* 두칸씩 가는 포인터가 마지막에 도달하면 한칸 가는 포인터 위치가 중앙일거아니야
	* 그럼 그 포인터가 가리키는 노드가 L1의 마지막 노드. 그 바로 이후 노드가 L2의 첫번째 노드
	*
	* List* list1 = (List*)malloc(sizeof(List));
	* List* list2 = (List*)malloc(sizeof(List));
	*
	* list1->head->next = list->head->next;
	* list2->head->next = list->slow->next;
	* 근데 이러면 O(1) 공간만 사용하는게 맞나?
	*/