#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include<string.h>
#include"md5.h"

//更改用户密码（自己的）
void changeKey(sqlite3* db, char id[6]);

//给定ID，可查看其信息
void viewInformation(sqlite3* db, char id[6]);
void addUser(sqlite3* db);
void deleteUser(sqlite3* db, char id[6]);
void changeLevel(sqlite3* db, char id[6]);