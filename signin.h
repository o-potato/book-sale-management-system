#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include"md5.h"

//���ID�������Ƿ�ƥ��
int sign(sqlite3* db, char id[6], char nkey[21]);