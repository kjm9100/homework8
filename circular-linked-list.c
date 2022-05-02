#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h); // ����Ʈ �ʱ�ȭ �� ����� �����ϴ� �Լ� ����
int freeList(listNode* h); // ����Ʈ�� ���鿡 �Ҵ�� �޸� �����ϴ� �Լ� ����
int insertLast(listNode* h, int key); // ����Ʈ�� �������� ��� �����ϴ� �Լ� ����
int deleteLast(listNode* h); // ����Ʈ�� ������ ��带 �����ϴ� �Լ� ����
int insertFirst(listNode* h, int key); // ����Ʈ�� �� �տ� ��带 �����ϴ� �Լ� ����
int deleteFirst(listNode* h); // ����Ʈ�� �� �� ���(�����x)�� �����ϴ� �Լ� ����
int invertList(listNode* h); // ����Ʈ�� �������� ���ġ�ϴ� �Լ� ����

int insertNode(listNode* h, int key); // �Է°��� ���� ��� �����ϴ� �Լ� ����
int deleteNode(listNode* h, int key); // �Է°��� ���� ��� �����ϴ� �Լ� ����

void printList(listNode* h); // ����Ʈ ����ϴ� �Լ� ����



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("\n[----- [������] [2021041068] -----]\n\n");

	do{ // �޴� ���
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		// ���Ű ����
		printf("Command = ");
		scanf(" %c", &command);

		// ���õ� ���Ű�� ���� ���� ����
		switch(command) {
		case 'z': case 'Z':	// z, Z ���Ű ���� ��, ����Ʈ �ʱ�ȭ �� ����� ����
			initialize(&headnode);
			break;
		case 'p': case 'P':	// p, P ���Ű ���� ��, ����Ʈ ���
			printList(headnode);
			break;
		case 'i': case 'I':	// i, I ���Ű ���� ��, �Է°��� ���� ��带 ������ ����Ʈ�� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // d, D ���Ű ���� ��, ����Ʈ���� �Է°��� ���� ��带 ã�� ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':	// n, N ���Ű ���� ��, �Է°��� ���� ��带 ������ ����Ʈ�� �������� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // e, E ���Ű ���� ��, ����Ʈ�� ������ ��带 ����
			deleteLast(headnode);
			break;
		case 'f': case 'F':	// f, F ���Ű ���� ��, �Է°��� ���� ��带 ������ ����Ʈ�� �� �տ� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // t, T ���Ű ���� ��, ����Ʈ�� �� �� ��带 ����
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // r, R ���Ű ���� ��, ����Ʈ�� �������� ���ġ
			invertList(headnode);
			break;
		case 'q': case 'Q': // q, Q ���Ű ���� ��, ����Ʈ�� �������� �Ҵ�� �޸𸮸� ��� ����
			freeList(headnode);
			break;
		default: // �� �̿��� ���Ű ���� ��, ���� �޽��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q, Q ���Ű ���� ��, ���α׷� ����

	return 1;
}


int initialize(listNode** h) { // ����Ʈ �ʱ�ȭ �� ����� �����ϴ� �Լ�

	// ��� ��尡 �����ϸ�, ����Ʈ�� �Ҵ�� �޸� ��� ����
	if(*h != NULL)
		freeList(*h);

	// ����� ���� �� �ʱ�ȭ
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){ // ����Ʈ�� �Ҵ�� �޸� �����ϴ� �Լ�
	
		if(h->rlink == h)
	{
		free(h);
		return 0;
	}

	listNode* temp = h->llink; 

	// ������ ������ ó�� ������ �Ҵ�� �޸� ����
	while(temp != h)
	{
		temp = temp->llink;
		free(temp->rlink);
	}

	// ��� ��� �ʱ�ȭ
	temp->rlink = NULL;
	temp->llink = NULL;

	// ��� ��忡 �Ҵ�� �޸� ����
	free(h);

	return 0;
}



void printList(listNode* h) { // ����Ʈ�� ����ϴ� �Լ�
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // ����尡 ���� ���, ���� �޽��� ���
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) { // ����Ʈ�� ó�� ������ ������ ������ ���
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	// ������� ��ũ �ּҸ� Ȯ���ϱ� ���� ���
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) { // ����Ʈ�� ���� �� ��ũ�� �ּҸ� Ȯ���ϱ� ���� ��� 
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) { // �Է°��� ���� ��带 ������ ����Ʈ�� �������� �����ϴ� �Լ� 

	// �Է°��� ���� ��� ����
	listNode* NodetoInsert =(listNode*)malloc(sizeof(listNode));
	NodetoInsert->key = key;
	NodetoInsert->rlink = NodetoInsert->llink = NULL;

	// �Է°��� ���� ��带 ����Ʈ �������� ����
	NodetoInsert->rlink = h;
	NodetoInsert->llink = h->llink;
	h->llink->rlink = NodetoInsert;
	h->llink = NodetoInsert;

	return 1;
}

int deleteLast(listNode* h) { // ����Ʈ�� ������ ��带 �����ϴ� �Լ�

	if(h->rlink == h) // ����常 ������ ���, ���� �޽��� ���
	{
		printf("Nothing to delete.\n\n");
		return 1;
	}

	listNode* temp = h->llink;

	// ������ ������ ��� �ϳ� ���� ��带 ����
	h->llink = h->llink->llink;
	h->llink->rlink = h;	

	// ������ ��忡 �Ҵ�� �޸� ����
	temp->llink= NULL;
	temp->rlink= NULL;
	free(temp);

	return 1;
}

int insertFirst(listNode* h, int key) { // ����Ʈ�� �� �տ� �Է°��� ���� ��带 �����ϴ� �Լ�

	// �Է°��� ���� ��� ���� �� �ʱ�ȭ
	listNode* NodetoInsert =(listNode*)malloc(sizeof(listNode));
	NodetoInsert->key = key;
	NodetoInsert->llink = NodetoInsert->rlink = NULL;

	// ����Ʈ�� �� �տ� ������ ��带 ����
	NodetoInsert->rlink = h->rlink;
	NodetoInsert->llink = h;
	h->rlink->llink = NodetoInsert;
	h->rlink = NodetoInsert;
	
	return 1;
}

int deleteFirst(listNode* h) { // ����Ʈ�� ó�� ��带 �����ϴ� �Լ�

	if(h->rlink == h) // ����常 ������ ���, ���� �޽��� ���
	{
		printf("Nothing to delete.\n\n");
		return 1;
	}

	listNode* temp = h->rlink;

	// 2��° ���� ����带 ����
	h->rlink = temp->rlink;
	temp->rlink->llink = h;
	
	// 1��° ��忡 �Ҵ�� �޸� ����
	temp->rlink = NULL;
	temp->llink = NULL;
	free(temp);

	return 1;

}

int invertList(listNode* h) { // ����Ʈ�� �������� ���ġ�ϴ� �Լ�


	if(h->rlink == h || h == NULL) { // ����常 �����ϰų� ����尡 ���� ���, ���� �޽��� ���
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	// ����Ʈ�� �������� ���ġ�ϸ� ù ���� ������ ��尡 �ȴ�.
	h->llink = h->rlink;

	// ������ ������ �������� ���ġ�� �ӽ� ����
	while(n != NULL && n != h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	// �������� ���ġ�� ����Ʈ�� ����忡 ����
	h->rlink = middle;

	return 0;
}

int insertNode(listNode* h, int key) { // ����Ʈ�� ���� �߿��� �Է°����� ū ���� ���� ��� �ٷ� �տ� �Է°��� ���� ��带 �����ϴ� �Լ�

	// �Է°��� ���� ��带 ����
	listNode* NodetoInsert = (listNode*)malloc(sizeof(listNode));
	NodetoInsert->key = key;
	NodetoInsert->llink = NULL;
	NodetoInsert->rlink = NULL;

	if(h==h->rlink) // ����常 ������ ���, ����Ʈ�� �� �տ� �Է°��� ���� ��� ����
	{
		insertFirst(h,key);
		return 0;
	}

	listNode* Search_Node = h->rlink;

	while(Search_Node!=h) // ����Ʈ�� 1��° ������ ������ ������ �˻�
	{
		if(Search_Node->key >= key) // �˻��ϴ� ����� ���� �Է°����� Ŭ ���
		{
			if(Search_Node->llink==h) // �˻��ϴ� ��尡 1��° ����� ���, ����Ʈ�� �� �տ� �Է°��� ���� ��� ����
			{
				insertFirst(h,key);
				return 0;
			}
			else // �˻��ϴ� ��尡 �߰� ����� ���
			{
				// �˻��ϴ� ��� �ٷ� �տ� ����
				NodetoInsert->rlink = Search_Node;
				NodetoInsert->llink = Search_Node->llink;
				Search_Node->llink->rlink = NodetoInsert;
				Search_Node->llink = NodetoInsert;

				return 0;
			}
		}
		Search_Node = Search_Node->rlink;
	}

	insertLast(h,key); // ���������� �Է°����� ū ��带 ã�� ���� ���, ����Ʈ�� �������� ��带 ����

	return 0;
}

int deleteNode(listNode* h, int key) { // �Է°��� ���� ��带 �����ϴ� �Լ�

	if(h->rlink == h) // ����常 ���� ���, ���� �޽��� ���
	{
		printf("Nothing to delete.\n\n");
		return 0;
	}

	listNode* Search_Node = h->rlink;

	while(Search_Node!=h) // ������ ������ �˻�
	{
		if(Search_Node->key == key) // �Է°��� ������ ���� ���� ��带 ã�� ���
		{
			if(Search_Node->llink == h) // �Է°��� ������ ���� ���� ��尡 ����Ʈ�� ó�� ����� ���
			{
				deleteFirst(h); // ó�� ��� ����
				return 0;
			}
			else // �߰� ����̰ų� ������ ����� ���
			{
				// �ش� ��� ���� �� �޸� �Ҵ� ����
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

	// �Է°��� ������ ���� ���� ��尡 �������� ���� ���, ���� �޽��� ���
	printf("There is no node for the key.\n\n");

	return 0;
}


