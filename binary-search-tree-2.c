/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("[----------------- [Cho Daehyeon] [2016039075] -----------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);	// 재귀함수로 왼쪽 자식노드 계속 탐색
		printf(" [%d] ", ptr->key);		// 현재 key 출력
		recursiveInorder(ptr->right);	// 재귀함수로 오른쪽 자식노드 탐색
	}
}

void iterativeInorder(Node* node)
{
	for(;;)	// 무한루프
	{
		for(; node; node = node->left)
			push(node);		// 스택에 삽입
		node = pop();		// 스택에서 삭제

		if(!node) break;	// 노드가 null이면 break
		printf(" [%d] ", node->key);	// 현재 key 출력

		node = node->right;
	}
}

void levelOrder(Node* ptr)	// 루트 방문 -> 왼쪽 자식 방문 -> 오른쪽 자식 방문
{
	if(!ptr) return;

	enQueue(ptr);

	for(;;)	// 무한루프
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);	// 현재 key 출력

			if(ptr->left)
				enQueue(ptr->left);	// 왼쪽 자식노드가 있을 때 queue에 입력
			if(ptr->right)
				enQueue(ptr->right);// 오른쪽 자식노드가 있을 때 queue에 입력
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 삽입할 노드 생성
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {	// 이진트리가 비어있을 때
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		if(ptr->key == key) return 1;	// 삽입하려는 key가 이미 있을 때

		parentNode = ptr;

		if(ptr->key < key)	// 삽입하려는 key와 이진트리 비교
			ptr = ptr->right;	// key가 부모 노드보다 작으면 왼쪽 자식노드로 이동
		else
			ptr = ptr->left;	// key가 부모 노드보다 크면 오른쪽 자식노드로 이동
	}

	if(parentNode->key > key)
		parentNode->left = newNode;		// key가 부모 노드보다 작으면 왼쪽에 삽입
	else
		parentNode->right = newNode;	// key가 부모 노드보다 크면 오른쪽에 삽입
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {	
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;

	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {	// 삭제하려는 노드로 이동
		if(ptr->key != key) {

			parent = ptr;

			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	if(ptr == NULL)	
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	if(ptr->left == NULL && ptr->right == NULL)	// 리프 노드를 삭제할 때
	{
		if(parent != NULL) { 
			if(parent->left == ptr)		
				parent->left = NULL;	// 왼쪽 노드 삭제할 때
			else
				parent->right = NULL;	// 오른쪽 노드 삭제할 때
		} else {
			head->left = NULL;
		}

		free(ptr);
		return 1;
	}

	if ((ptr->left == NULL || ptr->right == NULL))	// 자식 노드가 하나 있는 노드 삭제할 때
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)		// 삭제할 노드와 자식 노드 교체
				parent->left = child;
			else
				parent->right = child;
		} else {
			root = child;
		}

		free(ptr);	// 노드 삭제
		return 1;
	}

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	while(candidate->left != NULL)	// 삭제할 노드의 오른쪽 자식 노드 중 가장 작은 노드 찾기
	{
		parent = candidate;
		candidate = candidate->left;
	}

	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	ptr->key = candidate->key;	// 오른쪽 자식 노드 중 가장 작은 노드와 삭제할 노드 교체

	free(candidate);	// 노드 삭제
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];	// 스택의 top 반환
}

void push(Node* aNode)	
{
	stack[++top] = aNode;	// 스택에 원소 추가
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	if (front == rear) {
		printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;	// 큐의 맨 앞 원소 반환
	return queue[front];

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;	// 큐의 맨 뒤에 원소 추가
}





