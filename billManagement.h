#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include<string.h>
#include<stdlib.h>

void insertAccount(sqlite3* db, char isbn[11], char id[6]);
void newBill(sqlite3* db);
void payBill(sqlite3* db, char isbn[11], char id[6]);
void cancelBill(sqlite3* db, char isbn[11]);
void viewAccount(sqlite3* db);
void viewBill(sqlite3* db, char isbn[11]);