#include"menu.h"
#include"init.h"
#include"signin.h"
//#include<winsqlite/winsqlite3.h>
#include <stdlib.h>
#include"sqlite3.h"
int main()
{
	sqlite3* db = NULL;
	int signin = 0;//����Ƿ�ɹ���¼
	char id[6];
	char key[21];

	//�������ݿ�
	int rc = sqlite3_open("book.db", &db);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "%s\n", sqlite3_errmsg(db));
		return -1;
	}
	else
		printf("Connect successfully!\n");

	//��Ϊ����ʹ�ã�����һ����������Ա
	if (checkInit(db) == 0)
	{
		//unsigned char k[21];
		printf("You are the first user of this system and you will be a super-user!\n");
		//scanf_s("%s", &k,21);
		signin = initDB(db);
		strcpy(id, "00001");
	}

	//��¼ϵͳ����signin����¼�Ƿ�ɹ���¼��signin = 1 Ϊ�ɹ���¼��signin = 0 Ϊδ�ܳɹ���¼
	while (!signin)
	{
		printf("----------SIGN IN----------\n");
		printf("Please enter your id: ");
		scanf_s("%s", &id, 6);
		printf("Please enter your keyword: ");
		scanf_s("%s", &key, 21);
		signin = sign(db, id, key);
		if (signin == 0)
		{
			printf("Do you want to try again?\n0.Yes\n1.No\n");
			scanf_s("%d", &signin);
			if (signin)
				exit(0);
		}
	}

	 
	char level[7];

	//��ȡ��ǰ�û���Ȩ�޼���
	if (signin)
	{
		char sql[128] = {};
		//char* errmsg;

		sprintf_s(sql, "select level from user where ID = '%s';", id);

		char** result;
		int rows;
		int cols;

		sqlite3_get_table(db, sql, &result, &rows, &cols, NULL);

		strcpy_s(level, result[cols]);
	}

	int cmd;

	//ִ�и��ֹ���
	while (signin)
	{
		if (strcmp(level, "super") == 0)
		{
			printSuperMenu();

			scanf_s("%d", &cmd);

			switch (cmd)
			{
			case 0: 
				sqlite3_close(db);
				exit(0);
			case 11:
				changeKey(db, id);
				break;
			case 12:
				viewInformation(db, id);
				break;
			case 13:
				aUserInfor(db);
				break;
			case 14:
				allInfor(db);
				break;
			case 15:
				addUser(db);
				break;
			case 16:
				removeUser(db);
				break;
			case 17:
				updateLevel(db);
				break;
			case 21:
				viewBookInfor(db);
				break;
			case 22:
				viewAllBook(db);
				break;
			case 23:
				updatePrice(db);
				break;
			case 24:
				bookArrive(db);//Ԥ�����鵽��������״̬����Ϊarrived�����Ҹı�����
				break;
			case 25:
				addBook(db);
				break;
			case 31:
				newBill(db);//��buylist�����һ���¼�¼�����ұ��Ϊδ����
				break;
			case 32:
				payBuyin(db, id);//���ö�����Ϊ�Ѹ���,������account�����¼�¼
				break;
			case 33:
				cancelBuyin(db);//ȡ��δ�����
				break;
			case 34:
				sellBill(db, id);//�۳�����,�ı��棬������account�����¼�¼
				break;
			case 35:
				viewAccount(db);//�鿴�˻���Ϣ
				break;
			case 36:
				viewBuylist(db);
				break;
			default:
				printf("Invalid cmd!\n");
				break;
			}
		}
		if (strcmp(level, "normal") == 0)
		{
			printNormalMenu();

			scanf_s("%d", &cmd);

			switch (cmd)
			{
			case 0:
				sqlite3_close(db);
				exit(0);
			case 11:
				changeKey(db, id);
				break;
			case 12:
				viewInformation(db, id);
				break;
			case 13:
				aUserInfor(db);
				break;
			case 14:
				allInfor(db);
				break;
			case 21:
				viewBookInfor(db);
				break;
			case 22:
				viewAllBook(db);
				break;
			case 23:
				updatePrice(db);
				break;
			case 24:
				bookArrive(db);//Ԥ�����鵽��������״̬����Ϊarrived�����Ҹı�����
				break;
			case 25:
				addBook(db);
				break;
			case 31:
				newBill(db);//��buylist�����һ���¼�¼�����ұ��Ϊδ����
				break;
			case 32:
				payBuyin(db, id);//���ö�����Ϊ�Ѹ���,������account�����¼�¼
				break;
			case 33:
				cancelBuyin(db);//ȡ��δ�����
				break;
			case 34:
				sellBill(db, id);//�۳�����,�ı��棬������account�����¼�¼
				break;
			case 35:
				viewAccount(db);//�鿴�˻���Ϣ
				break;
			case 36:
				viewBuylist(db);
				break;
			default:
				printf("Invalid cmd!\n");
				break;
			}
		}
	}
	return 0;
}