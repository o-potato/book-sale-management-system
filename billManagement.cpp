#include "billManagement.h"
#include "stockManagement.h"


void insertAccount(sqlite3* db, char isbn[11], char id[6])
{
	char billID[10];
	int typen;
	char type[7];
	//char book_name[51];
	//float fprice;
	int num;
	

	printf("Please enter the bill ID (e.g. The second bill on 5.1.2020 is encoded as 200501002): ");
	scanf("%s", &billID);
	printf("Is the bill sell or buy=in?\n1.sell\n2.buy-in\n");
	scanf("%d", &typen);
	switch (typen)
	{
	case 1: strcpy_s(type,"sell"); break;
	case 2: strcpy_s(type, "buy_in"); break;
	default: strcpy_s(type, "buy_in");
		break;
	}
	printf("Please enter the amount of books: ");
	scanf("%d", &num);

	char sql[512] = {};
	char* errmsg;
	
	sprintf_s(sql, "select price,book_name from backlist where isbn = '%s';", isbn);
	char** result;
	int rows;
	int cols;
	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	sprintf_s(sql, "select dealprice from buylist where isbn = '%s' and state = 'reserved';", isbn);
	char** result2;
	int rows2;
	int cols2;
	sqlite3_get_table(db, sql, &result2, &rows2, &cols2, NULL);

	sprintf_s(sql, "select sum(single_bill) from account where bill_ID < '%s';", billID);
	char** result3;
	int rows3;
	int cols3;
	sqlite3_get_table(db, sql, &result3, &rows3, &cols3, NULL);

	float singlesum, singlesum2;
	float totalsum;

	singlesum = num * atof(result[cols]);
	singlesum2 = num * atof(result2[cols2]);
	if (rows3 <= 1)
		totalsum = 10000000.00;
	else
		totalsum = 10000000.00 + atof(result3[cols3]);

	switch (typen)
	{
	case 1: sprintf_s(sql, "insert into account values('%s','%s','%s','%s',%.2f,'%s',%d,%f,%f);", billID, type, isbn, result[cols + 1], result[cols], id, num, singlesum, totalsum + singlesum); break;
	case 2: sprintf_s(sql, "insert into account values('%s','%s','%s','%s',%.2f,'%s',%d,%f,%f);", billID, type, isbn, result[cols + 1], result2[cols2], id, num, singlesum2, totalsum - singlesum2); break;
	default: sprintf_s(sql, "insert into account values('%s','%s','%s','%s',%.2f,'%s',%d,%f,%f);", billID, type, isbn, result[cols + 1], result2[cols2], id, num, singlesum2, totalsum - singlesum2);
		break;
	}

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Successfully insert a new record to account!\n");

	sqlite3_free_table(result);
	sqlite3_free_table(result2);
	sqlite3_free_table(result3);
}

void newBill(sqlite3* db)
{
	char isbn[11];
	float dealPrice;
	int amount;

	printf("Please enter ISBN: ");
	scanf("%s", &isbn);
	printf("Please enter the deal price(e.g.xxx.xx): ");
	scanf("%f", &dealPrice);
	printf("Please enter the amount: ");
	scanf("%d", &amount);

	char sql[128] = {};
	char* errmsg;

	sprintf_s(sql, "select * from backlist where ISBN = '%s';", isbn);

	char** result;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	if (rows == 0) addBook(db);//如果是新书，在backlist里加上其信息

	sprintf_s(sql, "insert into buylist values('%s',%.2f,%d,'n','reserved');", isbn, dealPrice, amount);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Successfully add a new book into the buy-list!\n");
}

void payBill(sqlite3* db, char isbn[11], char id[6])
{
	char sql[128] = {};
	char* errmsg;

	sprintf_s(sql, "select payment from buylist where isbn = '%s' and state = 'reserved';", isbn);

	char** result;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	if (*result[cols] == 'y')
		printf("The bill has been payed!\n");
	else
	{
		insertAccount(db, isbn, id);
		sprintf_s(sql, "update buylist set payment = 'y' where ISBN = '%s';", isbn);
		int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
		if (rc != SQLITE_OK)
			printf("%s\n", errmsg);
		else
			printf("Successfully pay!\n");
	}

	sqlite3_free_table(result);
}

void cancelBill(sqlite3* db, char isbn[11])
{
	char sql[128] = {};
	char* errmsg;

	sprintf_s(sql, "update buylist set state = 'returned' where ISBN = '%s' and state = 'reserved';", isbn);
	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Successfully cancel the bill!\n");
}

void viewAccount(sqlite3* db)
{
	char sql[128] = {};
	//char* errmsg;

	char left[10];
	char right[10];

	printf("Please enter the start date(e.g.2020.5.1 is 200501): ");
	scanf("%s", &left);
	printf("Please enter the end date(e.g.2020.5.1 is 200501): ");
	scanf("%s", &right);

	strcat_s(left, "000");
	right[5] += 1;
	strcat_s(right, "000");

	sprintf_s(sql, "select * from account where bill_ID > left and bill_ID < right;");

	char** result;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	int i, flag = 0;

	for (i = 0; i < (rows + 1) * cols; i++)
	{
		if ((flag++) == cols)
		{
			flag = 1;
			printf("\n");
		}
		printf("%s\t", result[i]);
	}
	printf("\n");

	sqlite3_free_table(result);
}

void viewBill(sqlite3* db, char isbn[11])
{
	char sql[128] = {};
	//char* errmsg;

	sprintf_s(sql, "select * from buylist where ISBN = '%s';", isbn);

	char** result;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	int index = cols;
	if (rows == 0)
	{
		printf("The book's bill doesn't exist!\n");
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
