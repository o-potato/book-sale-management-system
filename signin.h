#pragma once
#include<stdio.h>
//#include<winsqlite/winsqlite3.h>
#include"sqlite3.h"
#include"md5.h"

//¼ì²éIDºÍÃÜÂëÊÇ·ñÆ¥Åä
int sign(sqlite3* db, char id[6], char nkey[21]);