#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

// ################################# ADT #################################

typedef int Data;

typedef struct _node {
	Data data;
	struct _node* left;
	struct _node* right;
}Node;

Node* createNode();

Node* findNode(Node* root, Data data);

void linkLeftSubTree(Node* main, Node* left);
void linkRightSubTree(Node* main, Node* right);

Data getData(Node* node);
Data getLeftData(Node* node);
Data getRightData(Node* node);

void setData(Node* node, Data data);

void deleteTree(Node* node);	

void inorderTraverse(Node* node);
void preorderTraverse(Node* node);
void postorderTraverse(Node* node);

void deleteTree(Node* node);

// ################################# main #################################

int main() {

	Node* root = createNode();
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int main, left, right;
		scanf("%d %d %d", &main, &left, &right);

		Node* mainNode = findNode(root, main); // 이미 트리에 있는지 찾기

		if (mainNode == NULL) { // 트리에 없으면 새로 생성
			mainNode = createNode();
			setData(mainNode, main);
			if (i == 0) { // 첫번째 입력의 노드는 루트 노드로 설정
				root = mainNode;
			}
		}

		if (left != 0) {
			Node* leftNode = findNode(root, left);
			if (leftNode == NULL) { // 트리에 없는 경우 새로 생성
				leftNode = createNode();
				setData(leftNode, left);
			}
			linkLeftSubTree(mainNode, leftNode);
		}

		if (right != 0) {
			Node* rightNode = findNode(root, right);
			if (rightNode == NULL) { // 트리에 없는 경우 새로 생성
				rightNode = createNode();
				setData(rightNode, right);
			}
			linkRightSubTree(mainNode, rightNode);
		}

	}

	int s;
	scanf("%d", &s);

	for (int i = 0; i < s; i++) {
		getchar();
		char* arr = (char*)malloc(sizeof(char) * n + 1);
		scanf("%s", arr);

		Node* current = root;

		if (current != NULL) {
			printf(" %d", getData(current));
		}

		for (int j = 0; j < strlen(arr); j++) {
			if (current == NULL) {
				//printf("Invalid path\n");
				break; // 경로가 잘못된 경우 루프를 종료
			}

			if (arr[j] == 'R') {
				printf(" %d", getRightData(current));
				current = current->right;
			}
			else if (arr[j] == 'L') {
				printf(" %d", getLeftData(current));
				current = current->left;
			}
		}
		printf("\n");
		free(arr);
	}

	deleteTree(root);

	return 0;
}

// ################################# functions #################################

Node* createNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

Node* findNode(Node* root, Data data) {
	if (root == NULL) return NULL;
	if (root->data == data) return root;

	Node* foundNode = findNode(root->left, data);
	if (foundNode == NULL) {
		foundNode = findNode(root->right, data);
	}
	return foundNode;
}

void linkLeftSubTree(Node* main, Node* left) {
	if (main != NULL)
	main->left = left;
}

void linkRightSubTree(Node* main, Node* right) {
	if (main != NULL)
	main->right = right;
}

Data getData(Node* node) {
	if (node == NULL) {
		return 0; // 또는 오류 코드 반환
	}
	return node->data;
}

Data getLeftData(Node* node) {
	if (node == NULL || node->left == NULL) {
		return 0; // 또는 오류 코드 반환
	}
	return getData(node->left);
}

Data getRightData(Node* node) {
	if (node == NULL || node->right == NULL) {
		return 0; // 또는 오류 코드 반환
	}
	return getData(node->right);
}

void setData(Node* node, Data data) {
	node->data = data;
}

void inorderTraverse(Node* node) { // 중위
	if (node->data == NULL) { 
		return;
	}
	inorderTraverse(node->left);
	printf("%c", node->data);
	inorderTraverse(node->right);
}

void preorderTraverse(Node* node) { // 전위 
	if (node->data == NULL) {
		return;
	}
	printf("%c", node->data);
	preorderTraverse(node->left);
	preorderTraverse(node->right);
}

void postorderTraverse(Node* node) { // 후위 
	if (node->data == NULL) {
		return;
	}
	postorderTraverse(node->left);
	postorderTraverse(node->right);
	printf("%c", node->data);
}

void deleteTree(Node* node) {
	if (node == NULL) return;

	deleteTree(node->left);
	deleteTree(node->right);
	free(node);
}

/*
input

9
5 3 9
3 8 15
8 0 2
2 0 0
15 0 0
9 7 10
7 12 0
12 0 0
10 0 0
3
RLL
LL
LR

*/
