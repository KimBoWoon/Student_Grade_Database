#include "Student_Grade_Database.h"

int main()
{
	Manager();
}
void MenuView()
{
	printf("********************************\n");
	printf("학생 데이터 베이스 관리 프로그램\n");
	printf("                 20113259 김보운\n");
	printf("********************************\n");
	printf("----------메뉴----------\n");
	printf("        1. 입력\n");
	printf("        2. 변경\n");
	printf("        3. 삭제\n");
	printf("        4. 출력\n");
	printf("        5. 파일 출력\n");
	printf("        6. 프로그램 종료\n");
	printf("------------------------\n");
	printf("어떤 작업을 하시겠습니까? ");
}
void Manager()
{
	FILE *file;
	StudentNode n;
	char Menu;

	n.Head = NULL;
	n.Tail = NULL;
	//n.Next = NULL;

	fopen_s(&file, "student.db", "a+");

	if (file == NULL)
	{
		printf("파일 개방 실패\n");
		exit(1);
	}
	else
		FileInput(file, &n);

	while (1)
	{
		MenuView();
		Menu = _getch();
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
			printf("프로그램을 종료합니다...\n");
			fclose(file);
			exit(0);
		default:
			printf("잘못된 입력입니다!\n");
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

		if (fscanf_s(file, "%s", NewNode->name, sizeof(NewNode->name)) == 1)
		{
			fscanf_s(file, "%d %lf", &NewNode->id, &NewNode->score);

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

	printf("이름 : ");
	scanf_s("%s", NewNode->name, sizeof(NewNode->name));
	printf("학번 : ");
	scanf_s("%d", &NewNode->id);
	printf("점수 : ");
	scanf_s("%lf", &NewNode->score);

	if (n->Head == NULL)
		n->Head = NewNode;
	else
		n->Tail->Next = NewNode;

	n->Tail = NewNode;

	printf("입력완료\n");
}
void StudentModify(StudentNode* n)
{
	Node* Modify = (Node *)malloc(sizeof(Node));
	char name[20];
	char choice;

	Modify = n->Head;

	printf("이름 : ");
	scanf_s("%s", name, sizeof(name));

	while (strcmp(Modify->name, name) != 0)
	{
		if (Modify->Next == NULL)
		{
			printf("존재 하지 않는 정보입니다!");
			return;
		}
		else
			Modify = Modify->Next;
	}

	printf("%s %d %.2lf\n", Modify->name, Modify->id, Modify->score);
	printf("변경 하시겠습니까? (y/n) : ");
	choice = _getch();
	printf("\n");

	if (choice == 'y' || choice == 'Y')
	{
		printf("이름 : ");
		scanf_s("%s", Modify->name, sizeof(Modify->name));
		printf("학번 : ");
		scanf_s("%d", &Modify->id);
		printf("점수 : ");
		scanf_s("%lf", &Modify->score);
		printf("변경 완료\n");
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

	printf("이름 : ");
	scanf_s("%s", name, sizeof(name));

	while (strcmp(Delete->name, name) != 0)
	{
		if (Delete->Next == NULL)
		{
			printf("존재 하지 않는 정보입니다!\n");
			return;
		}
		else
			Delete = Delete->Next;
	}

	printf("%s %d %.2lf\n", Delete->name, Delete->id, Delete->score);
	printf("제거 하시겠습니까? (y/n) : ");
	choice = _getch();
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
		printf("제거 완료!\n");
	}
	else
		return;
}
void StudentPrint(StudentNode* n)
{
	if (n->Head == NULL)
	{
		printf("입력된 데이터가 없습니다!\n");
		return;
	}

	char sorting;

	printf("이름순으로 출력은 1, 학번순으로 출력은 2, 성적순으로 출력은 3을 입력해주세요. ");
	sorting = _getch();
	printf("\n");

	if (sorting == '1')
		NameSort(n);
	else if (sorting == '2')
		StudentIDSort(n);
	else if (sorting == '3')
		ScoreSort(n);

	Node* cur = (Node *)malloc(sizeof(Node));
	cur = n->Head;

	printf("이름		학번		성적\n");
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
		printf("입력된 데이터가 없습니다!\n");
		return;
	}
	else
		printf("지금까지 기록한 정보를 파일에 기록합니다...\n");

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
void Swap(Node* n, Node* m)
{
	Node* temp = (Node *)malloc(sizeof(Node));

	strcpy_s(temp->name, sizeof(temp->name), n->name);
	strcpy_s(n->name, sizeof(n->name), m->name);
	strcpy_s(m->name, sizeof(m->name), temp->name);

	temp->id = n->id;
	n->id = m->id;
	m->id = temp->id;

	temp->score = n->score;
	n->score = m->score;
	m->score = temp->score;
}
void StudentFree(Node* n)
{
	free(n);
	n = NULL;
}