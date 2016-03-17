#ifndef __STUDENT_GRADE_DATABASE__
#define __STUDENT_GRADE_DATABASE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <WinSock2.h>
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")
#pragma comment(lib, "ws2_32.lib")

#define  DB_HOST  "localhost"
#define  DB_USER  "Practice"
#define  DB_PASS  "1234"
#define  DB_PORT  3306
#define  DB_NAME  "Student"

void MenuView();
void Manager(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row);
void StudentInput(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row);
void StudentModify(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row);
void StudentDelete(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row);
void StudentPrint(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row);
void StudentFilePrint(MYSQL *pConnection, MYSQL conn, MYSQL_RES* pSQL_result, MYSQL_ROW SQL_row);

#endif