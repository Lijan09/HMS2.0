// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

using namespace std;

void makeTable();  // Function declaration
void insertTable(string id, string name, string pwd, string pos);
void deleteTable(string id);
void updateTable(string id, string name, string pwd, string pos);

int checkAdminPwd(string name, string pwd);
int checkDocPwd(string name, string pwd);
int checkRecpPwd(string name, string pwd);

void makePatient();
void insertPatient(string id, string name, string pwd);
void deletePatient(string id);
void updatePatient(string id, string name, string pwd, string meds);

#endif // FUNCTIONS_H
