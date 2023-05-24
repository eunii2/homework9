/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

// 이진 탐색 트리의 노드에 대한 구조 정의
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h); // 이진 탐색 트리 초기화

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void freeNode(Node* ptr);

int main()
{
	printf("[-----[Choi Gaeun][2022078054]-----]");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

// 이진 탐색 트리를 초기화 하는 함수, 이미 트리가 존재하면 해당 트리를 해제한 후 새로 생성
int initializeBST(Node** h) {

	if(*h != NULL)
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

// 중위 순회를 수행하는 재귀 함수, 왼쪽 노드 -> 루트 노드 -> 오른쪽 노드 순으로 출력
void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

// 전위 순회를 수행하는 재귀 함수, 루트 노드 -> 왼쪽 노드 -> 오른쪽 노드 순으로 출력
void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

// 후위 순회를 수행하는 재귀 함수, 왼쪽 노드 -> 오른쪽 노드 -> 루트 노드 순으로 출력
void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

// 이진 탐색 트리에서 노드를 삽입하는 함수, 먼저 새 노드를 생성하고 트리를 순회하면서 적절한 위치를 찾아 삽입
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}
	
	Node* ptr = head->left;
	Node* parentNode = NULL;

	while(ptr != NULL) {
		if(ptr->key == key) return 1;

		parentNode = ptr;

		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// 키에 해당하는 잎 노들르 삭제하는 함수, 해당 노드가 잎 노드가 아니면 삭제 안함
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {
				if(parentNode == head)
					head->left = NULL;
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;
				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		parentNode = ptr;

		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

// 키에 해당하는 노드를 재귀적으로 찾는 함수. 찾지 못하면 NULL 반환
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	return ptr;

}

// 키에 해당하는 노드를 반복적으로 찾는 함수. 찾지 못하면 NULL 반환
Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

// 트리에 할당된 모든 메모리를 해제하는 함수. 모든 노드를 순회하며 freeNode 함수를 호출
int freeBST(Node* head)
{

	if(head->left == head){
		free(head);
		return 1;
	}
	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

// 노드에 할당된 메모리를 해제하는 함수. 재귀적으로 모든 하위 노드를 방문
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}