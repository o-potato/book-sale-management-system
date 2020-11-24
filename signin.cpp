#include "signin.h"
#include<string.h>

int sign(sqlite3* db, char id[6], char nkey[21])
{
	//unsigned char mkey[33];
	//char k[21];
	string s;
	//strcpy_s(mkey, (char*)MD5(nkey));
	
	s = nkey;
	s = MD5(s).toStr();

	char sql[128] = {};

	sprintf_s(sql, "select key from user where ID = '%s';", id);

	char** result = NULL;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	if (rows == 0)
	{
		printf("The user doesn't exist!\n");
		sqlite3_free_table(result);
		return 0;
	}
	else
	{
		string re;
		re = result[cols];
		//printf("%s\n",re);
		if (re == s)
		{
			sqlite3_free_table(result);
			return 1;
		}
		else
		{
			printf("Your ID or keyword is wrong!\n");
			sqlite3_free_table(result);
			return 0;
		}
	}
}
