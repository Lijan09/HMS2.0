// globals.h
#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include "sqlite3.h"
#include <iostream>

using namespace std;

extern int totalData;
extern string globalName;
extern sqlite3 *db;
extern sqlite3_stmt *stmt;
extern int result;
extern string query;

extern sqlite3 *pdb;
extern sqlite3_stmt *pstmt;
extern int presult;
extern string pquery;  // Declaration of the global variable


class Data{
public:
    string id, name, pwd, pos;
};

#endif // GLOBALS_H
