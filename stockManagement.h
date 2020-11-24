#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include<string.h>
#include<stdlib.h>

//查看指定书的信息
void viewBook(sqlite3* db, char isbn[11]);

//改变指定书的价格
void changePrice(sqlite3* db, char isbn[11]);

//更新指定书的库存量
void changeStock(sqlite3* db, char isbn[11]);

//增加新书的记录
void addBook(sqlite3* db);