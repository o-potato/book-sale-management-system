#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include<string.h>
#include"md5.h"

//�����û����루�Լ��ģ�
void changeKey(sqlite3* db, char id[6]);

//����ID���ɲ鿴����Ϣ
void viewInformation(sqlite3* db, char id[6]);
void addUser(sqlite3* db);
void deleteUser(sqlite3* db, char id[6]);
void changeLevel(sqlite3* db, char id[6]);