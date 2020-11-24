#include "userManagement.h"

void changeKey(sqlite3* db, char id[6])
{
	char nkey[21];
	//unsigned char mkey[17];

	printf("Please enter your new key(no more than 20 chars): ");
	scanf_s("%s", nkey, 21);
	//strcpy_s((char*)mkey, 17, (char*)MD5(nkey));
	string s;
	s = nkey;
	s = MD5(s).toStr();
	char ss[33];
	strcpy(ss, s.c_str());

	char sql[128] = {};
	char* errmsg;

	sprintf_s(sql, "update user set key = '%s' where ID = '%s';", ss, id);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Change your keyword successfully!\n");
}

void viewInformation(sqlite3* db, char id[6])
{
	char sql[128] = {};
	//char* errmsg;

	sprintf_s(sql, "select ID,name,gender,age,level from user where ID = '%s';", id);

	char** result;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	int index = cols;
	if (rows == 0)
	{
		printf("The user doesn't exist!\n");
		sqlite3_free_table(result);
	}
	else
	{
		for (int i = 0; i < cols; i++)
		{
			printf("%s ", result[index]);
			index++;
		}
		printf("\n");
	}
}

void addUser(sqlite3* db)
{
	char id[6], name[21], gender[2], level[7];
	int age;
	printf("Please enter the information of the new user:\n");
	printf("ID: ");
	scanf_s("%s", &id, 6);
	printf("name: ");
	scanf_s("%s", &name, 21);
	printf("gender(m/f): ");
	scanf_s("%s", &gender, 2);
	printf("age: ");
	scanf_s("%d", &age);
	printf("level(super/normal): ");
	scanf_s("%s", &level, 7);

	//unsigned char nkey[21] = { '1','2','3','4','5','6' };
	//unsigned char mkey[17];
	//strcpy_s((char*)mkey, 17, (char*)MD5(nkey));
	char k[21] = "123456";
	string s = k;
	s = MD5(s).toStr();
	char ss[33];
	strcpy(ss, s.c_str());

	char sql[128];
	char* errmsg;

	sprintf_s(sql, "insert into user values('%s','%s','%s',%d,'%s','%s');", id, name, gender, age, ss, level);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);

	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("A new user is created!\nThe initial keyword is 123456.\nYou can change it later.\n ");
}

void deleteUser(sqlite3* db, char id[6])
{ 
	char sql[128] = {};
	char* errmsg;

	sprintf_s(sql, "delete from user where ID = '%s';", id);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Successfully delete the user!\n");
}

void changeLevel(sqlite3* db, char id[6])
{
	char sql1[128] = {};
	char sql2[128] = {};
	char* errmsg;

	char nlevel[7];
	
	sprintf_s(sql1, "select level form user where ID = '%s';", id);

	printf("The current level of the user is: ");
	sqlite3_exec(db, sql1, NULL, NULL, &errmsg);
	printf("\nPlease enter new level: ");
	scanf_s("%s", &nlevel, 7);

	sprintf_s(sql2, "update user set level = '%s' where ID = '%s';", nlevel, id);

	int rc = sqlite3_exec(db, sql2, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s", errmsg);
	else
		printf("Successfully update the level!\n");
}
