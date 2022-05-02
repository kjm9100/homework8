#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h); // 리스트 초기화 및 헤드노드 생성하는 함수 선언
int freeList(listNode* h); // 리스트의 노드들에 할당된 메모리 해제하는 함수 선언
int insertLast(listNode* h, int key); // 리스트의 마지막에 노드 삽입하는 함수 선언
int deleteLast(listNode* h); // 리스트의 마지막 노드를 삭제하는 함수 선언
int insertFirst(listNode* h, int key); // 리스트의 맨 앞에 노드를 삽입하는 함수 선언
int deleteFirst(listNode* h); // 리스트의 맨 앞 노드(헤드노드x)를 삭제하는 함수 선언
int invertList(listNode* h); // 리스트를 역순으로 재배치하는 함수 선언

int insertNode(listNode* h, int key); // 입력값을 가진 노드 삽입하는 함수 선언
int deleteNode(listNode* h, int key); // 입력값을 가진 노드 삭제하는 함수 선언

void printList(listNode* h); // 리스트 출력하는 함수 선언



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("\n[----- [김지민] [2021041068] -----]\n\n");

	do{ // 메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		// 명령키 선택
		printf("Command = ");
		scanf(" %c", &command);

		// 선택된 명령키에 따른 동작 수행
		switch(command) {
		case 'z': case 'Z':	// z, Z 명령키 선택 시, 리스트 초기화 및 헤드노드 생성
			initialize(&headnode);
			break;
		case 'p': case 'P':	// p, P 명령키 선택 시, 리스트 출력
			printList(headnode);
			break;
		case 'i': case 'I':	// i, I 명령키 선택 시, 입력값을 가진 노드를 생성해 리스트에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // d, D 명령키 선택 시, 리스트에서 입력값을 가진 노드를 찾아 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':	// n, N 명령키 선택 시, 입력값을 가진 노드를 생성해 리스트의 마지막에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // e, E 명령키 선택 시, 리스트의 마지막 노드를 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F':	// f, F 명령키 선택 시, 입력값을 가진 노드를 생성해 리스트의 맨 앞에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // t, T 명령키 선택 시, 리스트의 맨 앞 노드를 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // r, R 명령키 선택 시, 리스트를 역순으로 재배치
			invertList(headnode);
			break;
		case 'q': case 'Q': // q, Q 명령키 선택 시, 리스트에 동적으로 할당된 메모리를 모두 해제
			freeList(headnode);
			break;
		default: // 그 이외의 명령키 선택 시, 오류 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q, Q 명령키 선택 시, 프로그램 종료

	return 1;
}


int initialize(listNode** h) { // 리스트 초기화 및 헤드노드 생성하는 함수

	// 헤드 노드가 존재하면, 리스트에 할당된 메모리 모두 해제
	if(*h != NULL)
		freeList(*h);

	// 헤드노드 생성 및 초기화
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){ // 리스트에 할당된 메모리 해제하는 함수
	
		if(h->rlink == h)
	{
		free(h);
		return 0;
	}

	listNode* temp = h->llink; 

	// 마지막 노드부터 처음 노드까지 할당된 메모리 해제
	while(temp != h)
	{
		temp = temp->llink;
		free(temp->rlink);
	}

	// 헤드 노드 초기화
	temp->rlink = NULL;
	temp->llink = NULL;

	// 헤드 노드에 할당된 메모리 해제
	free(h);

	return 0;
}



void printList(listNode* h) { // 리스트를 출력하는 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤드노드가 없을 경우, 오류 메시지 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) { // 리스트의 처음 노드부터 마지막 노드까지 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	// 헤드노드의 링크 주소를 확인하기 위한 출력
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) { // 리스트의 노드들 간 링크의 주소를 확인하기 위한 출력 
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) { // 입력값을 가진 노드를 생성해 리스트의 마지막에 삽입하는 함수 

	// 입력값을 가진 노드 생성
	listNode* NodetoInsert =(listNode*)malloc(sizeof(listNode));
	NodetoInsert->key = key;
	NodetoInsert->rlink = NodetoInsert->llink = NULL;

	// 입력값을 가진 노드를 리스트 마지막에 삽입
	NodetoInsert->rlink = h;
	NodetoInsert->llink = h->llink;
	h->llink->rlink = NodetoInsert;
	h->llink = NodetoInsert;

	return 1;
}

int deleteLast(listNode* h) { // 리스트의 마지막 노드를 삭제하는 함수

	if(h->rlink == h) // 헤드노드만 존재할 경우, 오류 메시지 출력
	{
		printf("Nothing to delete.\n\n");
		return 1;
	}

	listNode* temp = h->llink;

	// 헤드노드와 마지막 노드 하나 앞의 노드를 연결
	h->llink = h->llink->llink;
	h->llink->rlink = h;	

	// 마지막 노드에 할당된 메모리 해제
	temp->llink= NULL;
	temp->rlink= NULL;
	free(temp);

	return 1;
}

int insertFirst(listNode* h, int key) { // 리스트의 맨 앞에 입력값을 가진 노드를 삽입하는 함수

	// 입력값을 가진 노드 생성 및 초기화
	listNode* NodetoInsert =(listNode*)malloc(sizeof(listNode));
	NodetoInsert->key = key;
	NodetoInsert->llink = NodetoInsert->rlink = NULL;

	// 리스트의 맨 앞에 생성한 노드를 삽입
	NodetoInsert->rlink = h->rlink;
	NodetoInsert->llink = h;
	h->rlink->llink = NodetoInsert;
	h->rlink = NodetoInsert;
	
	return 1;
}

int deleteFirst(listNode* h) { // 리스트의 처음 노드를 삭제하는 함수

	if(h->rlink == h) // 헤드노드만 존재할 경우, 오류 메시지 출력
	{
		printf("Nothing to delete.\n\n");
		return 1;
	}

	listNode* temp = h->rlink;

	// 2번째 노드와 헤드노드를 연결
	h->rlink = temp->rlink;
	temp->rlink->llink = h;
	
	// 1번째 노드에 할당된 메모리 해제
	temp->rlink = NULL;
	temp->llink = NULL;
	free(temp);

	return 1;

}

int invertList(listNode* h) { // 리스트를 역순으로 재배치하는 함수


	if(h->rlink == h || h == NULL) { // 헤드노드만 존재하거나 헤드노드가 없을 경우, 오류 메시지 출력
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	// 리스트를 역순으로 재배치하면 첫 노드는 마지막 노드가 된다.
	h->llink = h->rlink;

	// 마지막 노드까지 역순으로 재배치해 임시 저장
	while(n != NULL && n != h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	// 역순으로 재배치한 리스트를 헤드노드에 전달
	h->rlink = middle;

	return 0;
}

int insertNode(listNode* h, int key) { // 리스트의 노드들 중에서 입력값보다 큰 값을 가진 노드 바로 앞에 입력값을 가진 노드를 삽입하는 함수

	// 입력값을 가진 노드를 생성
	listNode* NodetoInsert = (listNode*)malloc(sizeof(listNode));
	NodetoInsert->key = key;
	NodetoInsert->llink = NULL;
	NodetoInsert->rlink = NULL;

	if(h==h->rlink) // 헤드노드만 존재할 경우, 리스트의 맨 앞에 입력값을 가진 노드 삽입
	{
		insertFirst(h,key);
		return 0;
	}

	listNode* Search_Node = h->rlink;

	while(Search_Node!=h) // 리스트의 1번째 노드부터 마지막 노드까지 검색
	{
		if(Search_Node->key >= key) // 검색하는 노드의 값이 입력값보다 클 경우
		{
			if(Search_Node->llink==h) // 검색하는 노드가 1번째 노드일 경우, 리스트의 맨 앞에 입력값을 가진 노드 삽입
			{
				insertFirst(h,key);
				return 0;
			}
			else // 검색하는 노드가 중간 노드일 경우
			{
				// 검색하는 노드 바로 앞에 삽입
				NodetoInsert->rlink = Search_Node;
				NodetoInsert->llink = Search_Node->llink;
				Search_Node->llink->rlink = NodetoInsert;
				Search_Node->llink = NodetoInsert;

				return 0;
			}
		}
		Search_Node = Search_Node->rlink;
	}

	insertLast(h,key); // 마지막까지 입력값보다 큰 노드를 찾지 못할 경우, 리스트의 마지막에 노드를 삽입

	return 0;
}

int deleteNode(listNode* h, int key) { // 입력값을 가진 노드를 삭제하는 함수

	if(h->rlink == h) // 헤드노드만 있을 경우, 오류 메시지 출력
	{
		printf("Nothing to delete.\n\n");
		return 0;
	}

	listNode* Search_Node = h->rlink;

	while(Search_Node!=h) // 마지막 노드까지 검색
	{
		if(Search_Node->key == key) // 입력값과 동일한 값을 가진 노드를 찾을 경우
		{
			if(Search_Node->llink == h) // 입력값과 동일한 값을 가진 노드가 리스트의 처음 노드일 경우
			{
				deleteFirst(h); // 처음 노드 삭제
				return 0;
			}
			else // 중간 노드이거나 마지막 노드일 경우
			{
				// 해당 노드 삭제 및 메모리 할당 해제
				Search_Node->llink->rlink = Search_Node->rlink;
				Search_Node->rlink->llink = Search_Node->llink;
				Search_Node->llink = NULL;
				Search_Node->rlink = NULL;

				free(Search_Node);

				return 0;
			}
		}
		Search_Node = Search_Node->rlink;
	}

	// 입력값과 동일한 값을 가진 노드가 존재하지 않을 경우, 오류 메시지 출력
	printf("There is no node for the key.\n\n");

	return 0;
}


