/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { //노드 구조체 생성, 키, 왼쪽링크, 오른쪽 링크
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("[-------[황슬비] [2018032027] ------");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) { //이중포인터로 받음, call by refence
	if(*h != NULL) //h->first가 NULL이 아니면 freeList호출하여 메모리 해제
			freeList(*h);

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //새로운 노드 할당하여 h가 가리키도록 함
	temp->first = NULL;
	(*h)=temp;
	return 1;
}

int freeList(headNode* h){
	listNode* p = h->first;
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
		}free(h);

	return 0;
}


void printList(headNode* h) { //싱글포인터 h
	int i = 0;
	listNode* p; //싱글포인터 p 추가

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);

	//삭제하기
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node:  [rlink]=%p\n", h->first);

	i = 0;
	p = h->first;
	while(p != NULL) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if(h==NULL){ //전처리검사
			insertFirst(h,key);
		}
		else{
			listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트노드 생성
			listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
			node->key=key;
			node->rlink=NULL; //node는 마지막 값이므로 rlink에 NULL을 넣어준다.
			temp=h->first;

				while(temp->rlink !=NULL){ //temp가 마지막에 위치하도록
					temp=temp->rlink; //오른쪽 링크타고 계속 감
				}
				temp->rlink=node;//NULL인 rlink에 node연결
				node->llink=temp; //node의 llink에 temp연결
		}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first==NULL){ //전처리검사
					printf("Linked List is empty!!!!!");
					return 0;
				}

		listNode* temp = (listNode*)malloc(sizeof(listNode)); //삭제할 노드
		temp=h->first;
		if(temp->rlink==NULL){ //리스트에 노드가 하나인 경우
			free(temp); //바로 할당 해제
			h->first = NULL; //헤드의 포인터 NULL로
			return 0;
		}
		else{ //노드 두개 이상인 경우
			temp=temp->rlink;
			while(temp->rlink !=NULL){
				temp = temp -> rlink;
			} //삭제할 노드의 rlink가 NULL인 경우 (마지막 노드인 경우)
			temp->llink->rlink=NULL; //선행노드의 rlink를 NULL로 설정
			free(temp); //노드 삭제
		}


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성

	node->key = key; //새로운 노드에 key값 넣어줌
	node->llink=NULL; //노드의 양쪽 링크 NULL로 초기화
	node->rlink=NULL;
	h->first = node; //헤드노드에 연결

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h->first==NULL){
			printf("Linked List is empty!!!!!");
			return 0;
		}

		listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
		temp=h->first;
		h->first=temp->rlink;
		if(temp->rlink !=NULL){
			temp->rlink->llink=NULL;
		}
		free(temp);
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first==NULL){
		printf("Linked List is empty!!!!!\n");
		return 0;
	}
	listNode *temp, *p;
		p=h->first;
		if(p->rlink==NULL){ //노드가 하나인 경우 그냥 리턴
			return 0;
		}
	while(p != NULL){ //순회하며 링크 변경
		temp =p->llink;
		p->llink=p->rlink;
		p->rlink=temp;
		p=p->llink;
	}
	temp=temp->llink;
	h->first=temp; //헤드와 temp연결

}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	if( h->first==NULL){ //공백리스트인경우
			insertFirst(h,key);
			return 0;
		}

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
	node->key = key;
	temp=h->first;
	if(temp->key>=key){ //비교연산
			node->rlink=temp;
			node->llink=NULL;
			h->first=node;
			}
		else{
			while(1){
				if (temp->rlink ==NULL){ //노드가 한개인 경우
					temp->rlink=node;
					node->llink=temp;
					node->rlink=NULL;
					break;
				}
				else if (temp->rlink->key>key){//temp->key <= key < temp->link->key
					node->llink=temp;
					node->rlink=temp->rlink;
					temp->rlink=node;
					break;
				}
				else //범위에 해당하지 않으면 temp 한칸 옮김
					temp=temp->rlink;
			}
		}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if(h->first==NULL){
				printf("Linked List is empty!!!!!");
				return 0;
			}
		else{

		listNode* temp = (listNode*)malloc(sizeof(listNode)); //삭제할 노드
		temp=h->first;
		if(temp->key == key){ //첫번 째 노드가 key일 때
			deleteFirst(h);
		}

		while(temp !=NULL){ //노드검색
			temp=temp->rlink; //한칸씩 옮김
			if(temp->key == key){
				temp->llink->rlink=temp->rlink; //앞뒤 노드 서로 연결
				temp->rlink->llink=temp->llink;
				free(temp); //메모리해제
				return 0;
			}
		}

		if(temp==NULL){//key값이 노드에 없는 경우
		printf("Key is not founded in linked list\n");
			}
		}

	return 1;
}


