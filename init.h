#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include"md5.h"

//����Ƿ��ǿ�ϵͳ
int checkInit(sqlite3* db);

//����ϵͳ�趨��λ��������Ա
int initDB(sqlite3* db);

