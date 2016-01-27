#include "Student_Grade_Database.h"

int main()
{
	Manager();
}
void MenuView()
{
	printf("********************************\n");
	printf("�л� ������ ���̽� ���� ���α׷�\n");
	printf("                 20113259 �躸��\n");
	printf("********************************\n");
	printf("----------�޴�----------\n");
	printf("        1. �Է�\n");
	printf("        2. ����\n");
	printf("        3. ����\n");
	printf("        4. ���\n");
	printf("        5. ���� ���\n");
	printf("        6. ���α׷� ����\n");
	printf("------------------------\n");
	printf("� �۾��� �Ͻðڽ��ϱ�? ");
}
void Manager()
{
	FILE *file;
	StudentNode n;
	char Menu;

	n.Head = NULL;
	n.Tail = NULL;
	//n.Next = NULL;

	file = fopen("student.db", "a+");

	if (file == NULL)
	{
		printf("���� ���� ����\n");
		exit(1);
	}
	else
		FileInput(file, &n);

	while (1)
	{
		MenuView();
		scanf("%c", &Menu);
		printf("\n");

		switch (Menu)
		{
		case '1':
			StudentInput(&n);
			break;
		case '2':
			StudentModify(&n);
			break;
		case '3':
			StudentDelete(&n);
			break;
		case '4':
			StudentPrint(&n);
			break;
		case '5':
			StudentFilePrint(file, &n);
			break;
		case '6':
			printf("���α׷��� �����մϴ�...\n");
			fclose(file);
			exit(0);
		default:
			printf("�߸��� �Է��Դϴ�!\n");
			break;
		}
		system("pause");
		system("cls");
	}
}
void FileInput(FILE* file, StudentNode* n)
{
	int i;

	for (i = 0; !feof(file); i++)
	{
		Node* NewNode = (Node *)malloc(sizeof(Node));
		NewNode->Next = NULL;

		if (fscanf(file, "%s", NewNode->name) == 1)
		{
			fscanf(file, "%d %lf", &NewNode->id, &NewNode->score);

			if (n->Head == NULL)
				n->Head = NewNode;
			else
				n->Tail->Next = NewNode;

			n->Tail = NewNode;
		}
	}
}
void StudentInput(StudentNode* n)
{
	Node* NewNode = (Node *)malloc(sizeof(Node));
	NewNode->Next = NULL;

	printf("�̸� : ");
	scanf("%s", NewNode->name);
	printf("�й� : ");
	scanf("%d", &NewNode->id);
	printf("���� : ");
	scanf("%lf", &NewNode->score);

	if (n->Head == NULL)
		n->Head = NewNode;
	else
		n->Tail->Next = NewNode;

	n->Tail = NewNode;

	printf("�Է¿Ϸ�\n");
}
void StudentModify(StudentNode* n)
{
	Node* Modify = (Node *)malloc(sizeof(Node));
	char name[20];
	char choice;

	Modify = n->Head;

	printf("�̸� : ");
	scanf("%s", name);

	while (strcmp(Modify->name, name) != 0)
	{
		if (Modify->Next == NULL)
		{
			printf("���� ���� �ʴ� �����Դϴ�!");
			return;
		}
		else
			Modify = Modify->Next;
	}

	printf("%s %d %.2lf\n", Modify->name, Modify->id, Modify->score);
	printf("���� �Ͻðڽ��ϱ�? (y/n) : ");
	scanf("%c", &choice);
	printf("\n");

	if (choice == 'y' || choice == 'Y')
	{
		printf("�̸� : ");
		scanf("%s", Modify->name);
		printf("�й� : ");
		scanf("%d", &Modify->id);
		printf("���� : ");
		scanf("%lf", &Modify->score);
		printf("���� �Ϸ�\n");
	}
	else
		return;
}
void StudentDelete(StudentNode* n)
{
	Node* Delete = (Node *)malloc(sizeof(Node));
	char name[20];
	char choice;

	Delete = n->Head;

	printf("�̸� : ");
	scanf("%s", name);

	while (strcmp(Delete->name, name) != 0)
	{
		if (Delete->Next == NULL)
		{
			printf("���� ���� �ʴ� �����Դϴ�!\n");
			return;
		}
		else
			Delete = Delete->Next;
	}

	printf("%s %d %.2lf\n", Delete->name, Delete->id, Delete->score);
	printf("���� �Ͻðڽ��ϱ�? (y/n) : ");
	scanf("%c", &choice);
	printf("\n");

	if (choice == 'y' || choice == 'Y')
	{
		if (Delete == n->Head)
			n->Head = n->Head->Next;
		else
		{
			Node* Before = (Node *)malloc(sizeof(Node));
			Before = n->Head;

			while (strcmp(Before->Next->name, name) != 0)
				Before = Before->Next;

			Before->Next = Delete->Next;
		}

		StudentFree(Delete);
		printf("���� �Ϸ�!\n");
	}
	else
		return;
}
void StudentPrint(StudentNode* n)
{
    char sorting;

	if (n->Head == NULL)
	{
		printf("�Էµ� �����Ͱ� �����ϴ�!\n");
		return;
	}

	printf("�̸������� ����� 1, �й������� ����� 2, ���������� ����� 3�� �Է����ּ���. ");
	scanf("%c", &sorting);
	printf("\n");

	if (sorting == '1')
		NameSort(n);
	else if (sorting == '2')
		StudentIDSort(n);
	else if (sorting == '3')
		ScoreSort(n);

	Node* cur = (Node *)malloc(sizeof(Node));
	cur = n->Head;

	printf("�̸�		�й�		����\n");
	printf("%s		%d	%.2lf\n", cur->name, cur->id, cur->score);
	while (cur->Next != NULL)
	{
		printf("%s		%d	%.2lf\n", cur->Next->name, cur->Next->id, cur->Next->score);
		cur = cur->Next;
	}
}
void StudentFilePrint(FILE* file, StudentNode* n)
{
	if (n->Head == NULL)
	{
		printf("�Էµ� �����Ͱ� �����ϴ�!\n");
		return;
	}
	else
		printf("���ݱ��� ����� ������ ���Ͽ� ����մϴ�...\n");

	Node* cur = (Node *)malloc(sizeof(Node));
	cur = n->Head;

	fprintf(file, "%s %d %.2lf\n", cur->name, cur->id, cur->score);
	while (cur->Next != NULL)
	{
		fprintf(file, "%s %d %.2lf\n", cur->Next->name, cur->Next->id, cur->Next->score);
		cur = cur->Next;
	}
}
void NameSort(StudentNode* n)
{
	Node* cur = (Node *)malloc(sizeof(Node));
	Node* cur2 = (Node *)malloc(sizeof(Node));
	cur = n->Head;
	cur2 = n->Head;

	while (cur->Next != NULL)
	{
		while (cur2->Next != NULL)
		{
			if (strcmp(cur2->name, cur2->Next->name) > 0)
				Swap(cur2, cur2->Next);
			cur2 = cur2->Next;
		}
		cur = cur->Next;
		cur2 = n->Head;
	}
}
void StudentIDSort(StudentNode* n)
{
	Node* cur = (Node *)malloc(sizeof(Node));
	Node* cur2 = (Node *)malloc(sizeof(Node));
	cur = n->Head;
	cur2 = n->Head;

	while (cur->Next != NULL)
	{
		while (cur2->Next != NULL)
		{
			if (cur2->id > cur2->Next->id)
				Swap(cur2, cur2->Next);
			cur2 = cur2->Next;
		}
		cur = cur->Next;
		cur2 = n->Head;
	}
}
void ScoreSort(StudentNode* n)
{
	Node* cur = (Node *)malloc(sizeof(Node));
	Node* cur2 = (Node *)malloc(sizeof(Node));
	cur = n->Head;
	cur2 = n->Head;

	while (cur->Next != NULL)
	{
		while (cur2->Next != NULL)
		{
			if (cur2->score > cur2->Next->score)
				Swap(cur2, cur2->Next);
			cur2 = cur2->Next;
		}
		cur = cur->Next;
		cur2 = n->Head;
	}
}
void Swap(Node *n, Node *m)
{
	Node* temp = (Node *)malloc(sizeof(Node));

	strcpy(temp->name, n->name);
	strcpy(n->name, m->name);
	strcpy(m->name, temp->name);

	temp->id = n->id;
	n->id = m->id;
	m->id = temp->id;

	temp->score = n->score;
	n->score = m->score;
	m->score = temp->score;
}
void StudentFree(Node *n)
{
	free(n);
	n = NULL;
}