#include "menu.h"

void printSuperMenu()
{
	printf("*************** M E N U ****************\n");
	printf("0.quit\n");
	printf("11.change my key              12.view my information          13.view a user's information      14.view all users' information\n");
	printf("15.add a user                 16.delete a user                17.change a user's level\n");
	printf("21.view a book's information  22.view all books' information  23.update a book's price          24.book arrive\n25.add a new book\n");
	printf("31.a new buy-in bill          32.pay for a buy-in bill        33.cancel a buy-in bill           34.a new sell bill                35.view account information\n");
	printf("36.view buy-list\n");
	printf("****************************************\n");
}

void printNormalMenu()
{
	printf("*************** M E N U ****************\n");
	printf("0.quit\n");
	printf("11.change my key              12.view my information          13.view a user's information      14.view all users' information\n");
	printf("21.view a book's information  22.view all books' information  23.update a book's price          24.book arrive\n25.add a new book\n");
	printf("31.a new buy-in bill          32.pay for a buy-in bill        33.cancel a buy-in bill           34.a new sell bill                35.view account information\n");
	printf("36.view buy-list\n");
	printf("****************************************\n");
}

void aUserInfor(sqlite3* db)
{
	char uid[6];
	
	printf("Please enter the ID of the user that you want to view: ");
	scanf("%s", &uid);

	viewInformation(db, uid);
}

void allInfor(sqlite3* db)
{
	char sql[128] = {};
	//char* errmsg;

	sprintf_s(sql, "select ID from user;");

	char** result;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	int index = cols;
	for (int i = 0; i < rows; i++)
	{
		viewInformation(db, result[index]);
		index++;
	}
}

void removeUser(sqlite3* db)
{
	char uid[6];

	printf("Please enter the ID of the user that you want to remove: ");
	scanf("%s", &uid);

	deleteUser(db, uid);
}

void updateLevel(sqlite3* db)
{
	char uid[6];

	printf("Please enter the ID of the user that you want to change the level: ");
	scanf("%s", &uid);

	changeLevel(db, uid);
}

void viewBookInfor(sqlite3* db)
{
	char isbn[11];

	printf("Please enter the ISBN of the book that you want to view: ");
	scanf("%s", &isbn);

	viewBook(db, isbn);
}

void viewAllBook(sqlite3* db)
{
	char sql[128] = {};
	//char* errmsg;

	sprintf_s(sql, "select ISBN from backlist;");

	char** result;
	int rows;
	int cols;

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

	int index = cols;
	for (int i = 0; i < rows; i++)
	{
		viewBook(db, result[index]);
		index++;
	}
}

void updatePrice(sqlite3* db)
{
	char isbn[11];

	printf("Please enter the ISBN of the book that you want to change the price: ");
	scanf("%s", &isbn);

	changePrice(db, isbn);
}

void payBuyin(sqlite3* db, char id[6])
{
	char isbn[11];

	printf("Please enter the ISBN of the bill that you have payed: ");
	scanf("%s", &isbn);

	payBill(db, isbn, id);

	insertAccount(db, isbn, id);
}

void cancelBuyin(sqlite3* db)
{
	char isbn[11];

	printf("Please enter the ISBN of the bill that you want to cancel: ");
	scanf("%s", &isbn);

	cancelBill(db, isbn);
}

void bookArrive(sqlite3* db)
{
	char isbn[11];

	printf("Please enter the arrived book's ISBN: ");
	scanf("%s", &isbn);

	char sql[128] = {};
	char* errmsg;

	/*char** result = NULL;
	int rows;
	int cols;

	sprintf_s(sql, "select * from backlist where ISBN = '%s';", isbn);

	sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);
	if (rows == 0)
		addBook(db);*/

	sprintf_s(sql, "update buylist set state = 'arrived' where ISBN = '%s' and state = 'reserved';", isbn);

	int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (rc != SQLITE_OK)
		printf("%s\n", errmsg);
	
	changeStock(db, isbn);
}

void sellBill(sqlite3* db, char id[6])
{
	char isbn[11];

	printf("Please enter the ISBN that you sell: ");
	scanf("%s", &isbn);

	changeStock(db, isbn);

	insertAccount(db, isbn, id);
}

void viewBuylist(sqlite3* db)
{
	int flag;
	printf("Do you want to check a specific book's bill or all bills?\n1.a specific book's bill    2.all bills\n");
	scanf("%d", &flag);
	if (flag == 1)
	{
		char isbn[11];
		printf("Please enter the ISBN of the book you want to check: ");
		scanf("%s", &isbn);

		viewBill(db, isbn);
	}
	else
	{
		char sql[128] = {};
		//char* errmsg;

		sprintf_s(sql, "select ISBN from buylist;");

		char** result;
		int rows;
		int cols;

		sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

		int index = cols;
		for (int i = 0; i < rows; i++)
		{
			viewBill(db, result[index]);
			index++;
		}
	}
}
