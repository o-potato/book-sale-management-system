#include "init.h"
#include<string.h>

int checkInit(sqlite3* db)
{
	char sql[128] = {};
	
	sprintf_s(sql, "select ID from user;");
	

	char** result=NULL;
	int rows;
	int cols;

	int rc = sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "%s\n", sqlite3_errmsg(db));
		return -1;
	}

	if (cols == 0)//no user
	{
		sqlite3_free_table(result);
		return 0;
	}
	else
	{
		sqlite3_free_table(result);
		return 1;
	}
}

int initDB(sqlite3* db)
{
	char k[21] = "123456";
	string s;
	//unsigned char key[33];
	//strcpy_s((char*)key, 33, (char*)MD5(k));
	s = k;
	s = MD5(s).toStr();
	char ss[33];
	strcpy(ss, s.c_str());

	char name[21];
	char gender[2];
	int age;

	printf("Please enter your name(no more than 20 chars): ");
	scanf_s("%s", &name,21);
	printf("Please enter your gender(m or f): ");
	scanf_s("%s", &gender,2);
	printf("Please enter your age: ");
	scanf("%d", &age);

	char sql[256] = {};
	char* errmsg;

	sprintf_s(sql, "insert into user values('00001','%s','%s',%d,'%s','super');", name, gender, age, ss);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return 0;
	}
	else
	{
		printf(" Your ID : 00001\nYour initial keyword : 123456 (You can change it later)\n");
		return 1;
	}
}
