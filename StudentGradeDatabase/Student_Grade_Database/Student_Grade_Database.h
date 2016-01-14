#ifndef __STUDENT_GRADE_DATABASE__
#define __STUDENT_GRADE_DATABASE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <tchar.h>
#include <Windows.h>

typedef struct Node {
	TCHAR name[20];
	INT_PTR id;
	DOUBLE score;
	struct Node* Next;
} Node;

typedef struct StudentNode {
	struct Node* Head;
	struct Node* Tail;
} StudentNode;

void MenuView();
void Manager();
void FileInput(FILE* file, StudentNode* n);
void StudentInput(StudentNode* n);
void StudentModify(StudentNode* n);
void StudentDelete(StudentNode* n);
void StudentPrint(StudentNode* n);
void StudentFilePrint(FILE* file, StudentNode* n);
void StudentFree(StudentNode* n);
void NameSort(StudentNode* n);
void StudentIDSort(StudentNode* n);
void ScoreSort(StudentNode* n);
void Swap(StudentNode* n, StudentNode* m);

#endif