#include "Student_Grade_Database.h"

#pragma warning(disable:4996)

int main()
{
	MYSQL *pConnection = NULL;
	MYSQL conn;
	MYSQL_RES* pSQL_result = NULL;
	MYSQL_ROW SQL_row = NULL;            // ������ �� ���� �迭�� ���� ����
	int nQuery_stat;        // ���� ���

	mysql_init(&conn);

	pConnection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0); // ���ϰ� Client �÷���

	if (pConnection == NULL) {
		printf("DB Connect Failed\n");
		return 0;
	}

	// �ѱ� ����� ���� ����
	mysql_query(pConnection, "SET SESSION character_set_connection=euckr;");
	mysql_query(pConnection, "SET SESSION character_set_results=euckr;");
	mysql_query(pConnection, "SET SESSION character_set_client=euckr;");

	Manager(pConnection, conn, pSQL_result, SQL_row);

	mysql_close(pConnection);
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
void Manager(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row)
{
	FILE *file;
	char Menu;

	while (1)
	{
		MenuView();
		Menu = _getch();
		printf("\n");

		switch (Menu)
		{
		case '1':
			StudentInput(pConnection, conn, pSQL_result, SQL_row);
			break;
		case '2':
			StudentModify(pConnection, conn, pSQL_result, SQL_row);
			break;
		case '3':
			StudentDelete(pConnection, conn, pSQL_result, SQL_row);
			break;
		case '4':
			StudentPrint(pConnection, conn, pSQL_result, SQL_row);
			break;
		case '5':
			StudentFilePrint(pConnection, conn, pSQL_result, SQL_row);
			break;
		case '6':
			printf("���α׷��� �����մϴ�...\n");
			exit(0);
		default:
			printf("�߸��� �Է��Դϴ�!\n");
			break;
		}
		system("pause");
		system("cls");
	}
}
void StudentInput(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row)
{
	int nQuery_stat;
	int id = -1;
	char name[20] = "";

	printf("�й� : ");
	scanf("%d", &id);
	printf("�̸� : ");
	scanf("%s", &name);

	char query[255];
	sprintf(query, "INSERT INTO STUDENT(ID, NAME) VALUES(%d, '%s');", id, name);

	nQuery_stat = mysql_query(pConnection, query);
	if (nQuery_stat != 0)
		printf("Data Insert Failed\n");
}
void StudentModify(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row)
{
	int nQuery_stat;
	int id = -1, choice = 0;
	char name[20] = "", query[255]="";

	printf("�й� : ");
	scanf("%d", &id);

	printf("�й� ���� : 1, �̸� ���� : 2\n");
	scanf("%d", &choice);
	if (choice == 1) {
		int setID = 0;
		printf("������ �й��� �Է��ϼ��� : ");
		scanf("%d", &setID);
		sprintf(query, "UPDATE STUDENT SET ID=%d WHERE ID=%d;", setID, id);
	}
	else if (choice == 2) {
		char setName[20] = "";
		printf("������ �̸��� �Է��ϼ��� : ");
		scanf("%s", &setName);
		sprintf(query, "UPDATE STUDENT SET NAME='%s' WHERE ID=%d;", setName, id);
	}

	nQuery_stat = mysql_query(pConnection, query);
	if (nQuery_stat != 0)
		printf("Data Modify Failed\n");
}
void StudentDelete(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row)
{
	int nQuery_stat;
	int id = -1;
	char name[20] = "";

	printf("�й� : ");
	scanf("%d", &id);

	char query[255];
	sprintf(query, "DELETE FROM STUDENT WHERE ID=%d;", id);

	nQuery_stat = mysql_query(pConnection, query);
	if (nQuery_stat != 0)
		printf("Data Delete Failed\n");
}
void StudentPrint(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row)
{
	char sorting;
	char* query = NULL;
	int nQuery_stat;

	printf("�й������� ����� 1, ��������� ����� 2, ���������� ����� 3�� �Է����ּ���. ");
	sorting = _getch();
	printf("\n");

	if (sorting == '1')
		query = "SELECT * FROM STUDENT.ENROL ORDER BY ID;";
	else if (sorting == '2')
		query = "SELECT * FROM STUDENT.ENROL ORDER BY RANK;";
	else if (sorting == '3')
		query = "SELECT * FROM STUDENT.ENROL ORDER BY GRADE;";

	nQuery_stat = mysql_query(pConnection, query);
	if (nQuery_stat != 0)
		printf("Data Search Error\n");

	pSQL_result = mysql_store_result(pConnection);
	printf("  �й�    �����ȣ       �߰�   �⸻    ����    �⼮     �հ�  ���   ����\n");
	while ((SQL_row = mysql_fetch_row(pSQL_result)) != NULL)
		printf("%s %s \t%s \t%s \t%s \t%s \t%s \t%s \t%s\n", SQL_row[0], SQL_row[1], SQL_row[2], SQL_row[3], SQL_row[4], SQL_row[5], SQL_row[6], SQL_row[7], SQL_row[8]);
	mysql_free_result(pSQL_result);
}
void StudentFilePrint(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row)
{
	FILE* file = fopen("student.txt", "w");
	int nQuery_stat;
	char* query = "SELECT * FROM STUDENT.ENROL ORDER BY RANK;";

	nQuery_stat = mysql_query(pConnection, query);
	if (nQuery_stat != 0)
		printf("Data Search Error\n");

	pSQL_result = mysql_store_result(pConnection);
	while ((SQL_row = mysql_fetch_row(pSQL_result)) != NULL)
		fprintf(file, "%s %s \t%s \t%s \t%s \t%s \t%s \t%s \t%s\n", SQL_row[0], SQL_row[1], SQL_row[2], SQL_row[3], SQL_row[4], SQL_row[5], SQL_row[6], SQL_row[7], SQL_row[8]);
	mysql_free_result(pSQL_result);
}