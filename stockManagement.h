#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include<string.h>
#include<stdlib.h>

//�鿴ָ�������Ϣ
void viewBook(sqlite3* db, char isbn[11]);

//�ı�ָ����ļ۸�
void changePrice(sqlite3* db, char isbn[11]);

//����ָ����Ŀ����
void changeStock(sqlite3* db, char isbn[11]);

//��������ļ�¼
void addBook(sqlite3* db);