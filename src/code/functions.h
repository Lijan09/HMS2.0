// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

using namespace std;

void makeTable();  // Function declaration
void insertTable(string id, string name, string pwd, string pos);
void deleteTable(string id);
int checkAdminPwd(string name, string pwd);

#endif // FUNCTIONS_H
