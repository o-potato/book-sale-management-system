#include "stockManagement.h"

void viewBook(sqlite3* db, char isbn[11])
{
	char sql[128] = {};
	//char* errmsg;

	sprintf_s(sql, "select * from backlist where ISBN = '%s';", isbn);

	char** result = NULL;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	int index = cols;
	for (int i = 0; i < cols; i++)
	{
		printf("%s ", result[index]);
		index++;
	}
	printf("\n");

	sqlite3_free_table(result);
}

void changePrice(sqlite3* db, char isbn[11])
{
	float nprice;

	printf("Please enter the new price(e.g. xxx.xx): ");
	scanf_s("%f", &nprice);

	char sql[128] = {};
	char* errmsg;

	sprintf_s(sql, "update backlist set price = %.2f where ISBN = '%s';", nprice, isbn);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Successfully update the price!\n");
}

void changeStock(sqlite3* db, char isbn[11])
{
	int dstock;

	printf("Please enter the change number of the stock(e.g. -100, 50): ");
	scanf("%d", &dstock);

	char sql1[128] = {};
	char sql2[128] = {};
	char* errmsg;

	char** result = NULL;
	int rows;
	int cols;

	sprintf_s(sql1, "select current_stock from backlist where ISBN = '%s';", isbn);
	sqlite3_get_table(db, sql1, &result, &rows, &cols, NULL);

	int stk;
	stk = atoi(result[cols]);
	sprintf_s(sql2, "update backlist set current_stock = %d where ISBN = '%s';", dstock + stk, isbn);

	int rc = sqlite3_exec(db, sql2, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Successfully update the stock!\n");

	sqlite3_free_table(result);
}

void addBook(sqlite3* db)
{
	char isbn[11];
	char book_name[51];
	char publisher[51];
	char author[21];
	float price;
	int current_stock;

	printf("Please enter the information of the new book: \n");
	printf("ISBN: ");
	scanf("%s", &isbn);
	printf("book_name: ");
	scanf("%s", &book_name);
	printf("publisher: ");
	scanf("%s", &publisher);
	printf("author: ");
	scanf("%s", &author);
	printf("price(e.g.xxx.xx): ");
	scanf("%f", &price);
	printf("current_stock: ");
	scanf("%d", &current_stock);

	char sql[128] = {};
	char* errmsg;

	sprintf_s(sql, "insert into backlist values('%s','%s','%s','%s',%.2f,%d);", isbn, book_name, publisher, author, price, current_stock);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	else
		printf("Successfully add a new book!\n");
}
