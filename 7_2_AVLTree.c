#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE  1
#define FALSE 0
#define NO_SUCH_KEY INT_MIN

typedef struct node_ {
	int key;
	int height;
	struct node_* lChild;
	struct node_* rChild;
	struct node_* parent;
}Node;

typedef struct tree_ {
	Node* root;
}Tree;

// 노드 생성
Node* makeNode();
// 탐색
int findElement(Node* root, int key);
Node* treeSearch(Node* v, int key);
// 삽입
void insertItem(Node** root, int key);
// 삭제
int removeElement(Node** root, int key);
Node* sibling(Node* w);
Node* inOrderSucc(Node* w);
Node* reduceExternal(Node** root, Node* z);
// 출력
void inorderTraversal(Node* root);
void preOrderTraversal(Node* root);
// etc
int isExternal(Node* w);
int isInternal(Node* w);
void expandExternal(Node* v);
void freeTree(Node* root);

// AVL
int updateHeight(Node* w);
void searchAndFixAfterInsertion(Node** root, Node* w);
void searchAndFixAfterRemoval(Node** root, Node* w);
int isBalanced(Node* w);
Node* restructure(Node** root, Node* x, Node* y, Node* z);

/*
test data

i 44
i 17
i 78
i 32
i 50
i 88
i 48
i 62
s 88
p
q

i 9
i 31
i 66
i 30
i 1
i 24
p
i 61
d 30
i 13

*/

int main() {
	char command;
	int quit = FALSE;
	int key;

	// init BST
	Tree tree;
	Node* root = makeNode();
	tree.root = root;

	// Loop
	while (!quit) {
		scanf(" %c", &command);

		switch (command) {
		case 'i':
			scanf("%d", &key);
			insertItem(&tree.root, key);
			break;

		case 'd':
			scanf("%d", &key);
			int removedKey = removeElement(&tree.root, key);
			if (removedKey == NO_SUCH_KEY) {
				printf("X\n");
			}
			else {
				printf("%d\n", removedKey);
			}
			break;

		case 's':
			scanf("%d", &key);
			Node* res = treeSearch(tree.root, key);
			if (res->key == INT_MIN) {
				printf("X\n");
			}
			else {
				printf("%d\n", res->key);
			}
			break;

		case 'p':
			//inorderTraversal(tree.root);
			preOrderTraversal(tree.root);
			printf("\n");
			break;

		case 'q':
			quit = TRUE;
			break;

		default:
			break;
		}
	}

	freeTree(tree.root); // 동적 할당 메모리 해제
	return 0;
}

Node* makeNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->lChild = NULL;
	newNode->rChild = NULL;
	newNode->parent = NULL;
	newNode->key = INT_MIN;
	newNode->height = 0;
	return newNode;
}

int findElement(Node* root, int key) {
	Node* w = treeSearch(root, key);

	if (isExternal(w)) {
		return NO_SUCH_KEY;
	}
	else {
		return w->key;
	}
}

Node* treeSearch(Node* v, int key) {
	if (isExternal(v)) {
		return v;
	}

	if (key == v->key) {
		return v;
	}
	else if (key < v->key) {
		return treeSearch(v->lChild, key);
	}
	else {
		return treeSearch(v->rChild, key);
	}
}

void insertItem(Node** root, int key) {
	Node* w = treeSearch(*root, key);

	if (isInternal(w)) { // 중복
		return;
	}
	else {
		w->key = key;
		expandExternal(w);
		// 1. 높이 먼저 업데이트 다 해주고
		updateHeight(w);
		// 2. avl 트리 속성에 맞게 개조
		searchAndFixAfterInsertion(root, w);
		return;
	}
}

// ############################################# AVL #############################################
int updateHeight(Node* w) {
	// 노드 w 의 높이를 갱신한 뒤 갱신 여부 반환
	// 갱신했으면 TRUE, 갱신하지 않았으면 FALSE 

	/*w->height += 1;
	while (w->parent != NULL) {
		if (w->parent->height == w->height) {
			w = w->parent;
			w->height += 1;
		}
		else {
			break;
		}
	}
	return TRUE;*/

	// 위 방식대로 코드 -> 삭제 했을때 업데이트가 고려되지 않음
	// 
	// 재귀적으로 현재 노드부터 부모까지 올라가며 높이를 갱신

	while (w != NULL) {

		int leftHeight = (w->lChild != NULL) ? w->lChild->height : 1;
		int rightHeight = (w->rChild != NULL) ? w->rChild->height : 1;

		int newHeight = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;

		// 기존 height랑 다르면 업데이트
		if (w->height != newHeight) {
			w->height = newHeight;
		}

		w = w->parent;
	}
	return TRUE;
}

void searchAndFixAfterInsertion(Node** root, Node* w) {
	// w에서 T의 루트를 향해 올라가다가 처음 만나는 불균형 노드를 z
	// z의 높은 자식을 y
	// y의 높은 자식을 x
	Node* z = NULL;
	while (w != NULL) { // 루트 부모까지 오면 반복 안되도록
		//printf("w로 들어온 key : %d\n", w->key);
		if (isBalanced(w)) {
			w = w->parent;
		}
		else {
			z = w; // 불균형 노드 z 발견 !
			break;
		}
	}
	if (z != NULL) { // 발견한 노드가 있다면 y, x 할당 후 개조
		Node* y = (z->rChild->height > z->lChild->height) ? z->rChild : z->lChild;
		Node* x = (y->rChild->height > y->lChild->height) ? y->rChild : y->lChild;
		Node* newSubTree = restructure(root, x, y, z);

		updateHeight(newSubTree);
	}
}

int isBalanced(Node* w) {
	// 두 자식 노드의 높이 차이를 비교
	// 균형이 맞으면 TRUE
	// 균형이 맞지 않으면 FALSE 반환
	int balance = w->lChild->height - w->rChild->height;
	if (balance >= -1 && balance <= 1)
		return TRUE;
	else
		return FALSE;
}

Node* restructure(Node** root, Node* x, Node* y, Node* z) {
	//printf("z : %d, y : %d, x : %d\n", z->key, y->key, x->key);

	// x, y, z를 알맞게 a, b, c에 넣고 a b c를 중위순회 순서에 맞게 재배치
	// 그럼 a, b, c 에 뭘 넣어야 함?
	// 중위순회 순서에 맞게 넣으면 된다

	// case 총 4가지
	// 단일 회전 2가지 : LL RR 
	// 이중 회전 2가지 : RL LR
	
	// (1) 단일회전 LL
	//	   z -> c
	//	 y -> b
	// x -> a
	// (2) 단일회전 RR
	// z -> a
	//   y -> b
	//     x -> c
	// (3) 이중회전 RL
	//   z -> a
	//      y -> c
	//    x -> b
	// (4) 이중회전 LR
	//     z ->c
	//  y -> a
	//    x -> b

	Node* a = NULL;
	Node* b = NULL;
	Node* c = NULL;

	Node* T1 = NULL;
	Node* T2 = NULL;
	Node* T3 = NULL;
	Node* T4 = NULL;


	if (z->lChild == y) { // y -> z
		if (y->lChild == x) { // x -> y -> z
			// LL 회전 케이스
			a = x;
			b = y;
			c = z;
			T1 = a->lChild;
			T2 = a->rChild;
			T3 = b->rChild;
			T4 = c->rChild;
		}
		else { // y -> x -> z
			// LR 회전 케이스
			a = y;
			b = x;
			c = z;
			T1 = a->lChild;
			T2 = b->lChild;
			T3 = b->rChild;
			T4 = c->rChild;
		}
	}
	else { // z -> y
		if (y->rChild == x) { // z -> y -> x
			// RR 회전 케이스
			a = z;
			b = y;
			c = x;
			T1 = a->lChild;
			T2 = b->lChild;
			T3 = c->lChild;
			T4 = c->rChild;
		}
		else { // z -> x -> y
			// RL 회전 케이스
			a = z;
			b = x;
			c = y;
			T1 = a->lChild;
			T2 = b->lChild;
			T3 = b->rChild;
			T4 = c->rChild;
		}
	}
	
	//a, b, c, T1, T2, T3, T4 할당 다됐고 재구성만 하면 ok
	//       b
	//   a        c
	//T1  T2   T3  T4

	b->parent = z->parent;

	// z가 루트였을 경우 
	// b는 루트가 되어야 함 => 루트 업데이트 해줘야 함
	if (b->parent == NULL) {
		*root = b;
	}
	else { // b->parent 를 z->parent로 바꿨으니 z->parent 의 자식으로 b를 변경
		if (z->parent->lChild == z) {
			z->parent->lChild = b;
		}
		else {
			z->parent->rChild = b;
		}
	}

	// a b c 재구성
	b->lChild = a;
	b->rChild = c;
	
	a->parent = b;
	c->parent = b;

	// T1, T2, T3, T4 재구성
	a->lChild = T1;
	a->rChild = T2;
	if (T1 != NULL) T1->parent = a;
	if (T2 != NULL) T2->parent = a;

	c->lChild = T3;
	c->rChild = T4;
	if (T3 != NULL) T3->parent = c;
	if (T4 != NULL) T4->parent = c;

	// 재구성 완료 -> 높이 업데이트
	updateHeight(a);
	updateHeight(c);
	updateHeight(b);
	
	return b;
}

//########################################### 삭제 관련 함수 #############################################

int removeElement(Node** root, int key) {
	Node* w = treeSearch(*root, key);

	if (isExternal(w)) {
		return NO_SUCH_KEY;
	}

	int rmKey = w->key; // 지울 key 미리 저장

	Node* z = w->lChild;
	Node* y = NULL;  
	Node* zs = NULL;
	if (!isExternal(z)) { // w->lChild가 내부노드라면
		z = w->rChild;
	}

	if (isExternal(z)) { // 하나라도 외부노드라면 여기  {case 1}
		zs = reduceExternal(root, z);
	}
	else { // lchild, rchild 둘다 내부노드라면 여기     {case 2}
		
		y = inOrderSucc(w);
		if (y != NULL) {
			w->key = y->key;
			z = y->lChild;
			zs = reduceExternal(root, z);
		}
	}
	if (zs != NULL) {
		searchAndFixAfterRemoval(root, zs->parent);
	}
	return rmKey;
}

void searchAndFixAfterRemoval(Node** root, Node* w) {
	// w부터 루트까지 올라가며 반복해서 수행
	while (w != NULL) {
		updateHeight(w);
		if (isBalanced(w)) {
			w = w->parent;
		}
		else {// 균형이 깨졌다면
			Node* z = w;
			Node* y;
			Node* x;

			// z의 높은 자식 y 선택
			if (z->lChild->height >= z->rChild->height) {
				y = z->lChild;
			}
			else {
				y = z->rChild;
			}

			// y의 높은 자식 x 선택
			if (y->lChild->height >= y->rChild->height) {
				x = y->lChild;
			}
			else {
				x = y->rChild;
			}

			// 재구조화 수행
			Node* newSubTree = restructure(root, x, y, z);

			// 재구조화 후 높이 업데이트
			updateHeight(newSubTree);

			// 재구조화된 부분의 부모 노드로 이동
			w = newSubTree->parent;
		}
	}
}


Node* sibling(Node* w) {
	Node* parent = w->parent;
	if (parent == NULL) {
		/*perror("invalidNodeException:sibling");
		exit(1);*/
	}
	if (parent->lChild == w) {
		return w->parent->rChild;
	}
	else {
		return w->parent->lChild;
	}
}

Node* inOrderSucc(Node* w) { // 한번 오른쪽 -> 쭉 왼쪽으로
	w = w->rChild;
	if (isExternal(w)) {
		return NULL;
	}
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}

Node* reduceExternal(Node** root, Node* z) { // z와 그 부모 노드를 삭제하고 z의 sibling을 올려준다
	Node* w = z->parent;
	Node* zs = sibling(z);

	if (w->parent == NULL) { 
		if (isExternal(zs)) {
			*root = NULL;
		}
		else {
			*root = zs;
			zs->parent = NULL;
		}
	}
	else {
		Node* g = w->parent;
		zs->parent = g;
		if (g->lChild == w) {
			g->lChild = zs;
		}
		else {
			g->rChild = zs;
		}
	}
	free(z);
	free(w);
	return zs;
}

//############################################# 기타 함수 #############################################

int isExternal(Node* w) {
	//if (w->lChild == NULL && w->rChild == NULL) {
	if (w->key == INT_MIN) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int isInternal(Node* w) {
	//if (w->lChild != NULL && w->rChild != NULL) {
	if (w->key != INT_MIN) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void expandExternal(Node* v) {
	v->lChild = makeNode();
	v->rChild = makeNode();

	v->lChild->parent = v;
	v->rChild->parent = v;
	return;
}

//############################################# 출력 및 메모리 해제 함수 #############################################
void inorderTraversal(Node* root) {
	//if (isExternal(root)) {
	if (root == NULL || root->key == INT_MIN) {
		return;
	}

	inorderTraversal(root->lChild);
	printf(" %d", root->key);
	//printf(" %d(%d)", root->key, root->height);
	inorderTraversal(root->rChild);
}

void preOrderTraversal(Node* root) {
	//if (isExternal(root)) {
	if (root == NULL || root->key == INT_MIN) {
		return;
	}

	printf(" %d", root->key);
	//printf(" %d(%d)", root->key, root->height);
	preOrderTraversal(root->lChild);
	preOrderTraversal(root->rChild);
}

void freeTree(Node* root) {
	if (root == NULL || isExternal(root)) {
		// 외부 노드이거나 NULL이면 아무 작업도 하지 않음
		return;
	}

	freeTree(root->lChild); // 왼쪽 서브트리 해제
	freeTree(root->rChild); // 오른쪽 서브트리 해제

	// 현재 노드 해제
	free(root);
}

