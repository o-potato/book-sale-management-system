#pragma once
#include"userManagement.h"
#include"stockManagement.h"
#include"billManagement.h"

//打印超级管理员的菜单
void printSuperMenu();

//打印普通管理员的菜单
void printNormalMenu();

//view a user's information
void aUserInfor(sqlite3* db);

//view all users' information
void allInfor(sqlite3* db);

//delete a user
void removeUser(sqlite3* db);

//change a user's level
void updateLevel(sqlite3* db);

//view a book's information
void viewBookInfor(sqlite3* db);

//view all books' information
void viewAllBook(sqlite3* db);

//update a book's price
void updatePrice(sqlite3* db);

//pay for a buy-in bill
void payBuyin(sqlite3* db, char id[6]);

//cancel a buy-in bill
void cancelBuyin(sqlite3* db);

//book arrive
void bookArrive(sqlite3* db);

//a new sell bill
void sellBill(sqlite3* db, char id[6]);

//view buylist by ISBN or view all buylist
void viewBuylist(sqlite3* db);