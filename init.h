#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include"md5.h"

//检查是否是空系统
int checkInit(sqlite3* db);

//给空系统设定首位超级管理员
int initDB(sqlite3* db);

