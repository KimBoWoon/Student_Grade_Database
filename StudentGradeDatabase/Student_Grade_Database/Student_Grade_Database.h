#ifndef __STUDENT_GRADE_DATABASE__
#define __STUDENT_GRADE_DATABASE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char name[20];
	int id;
	double score;
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
void StudentFree(Node* n);
void NameSort(StudentNode* n);
void StudentIDSort(StudentNode* n);
void ScoreSort(StudentNode* n);
void Swap(Node* n, Node* m);

#endif