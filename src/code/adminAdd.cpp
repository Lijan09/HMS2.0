#include "sqlite3.h"
#include <iostream>
#include "functions.h"
#include "globals.h"

using namespace std;

sqlite3 *db;
sqlite3_stmt *stmt;
int result;
string query;

void makeTable()
{

    if (sqlite3_open("hospital.db", &db) == SQLITE_OK)
    {

        query = "CREATE TABLE IF NOT EXISTS hospital(id VARCHAR(10), name varchar(30), pwd varchar(20), pos varchar(20));";

        result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
        int result1 = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result1 != SQLITE_DONE)
        {
            cout << "Error executing DELETE statement: " << sqlite3_errmsg(db) << endl;
        }
        if (result != SQLITE_OK)
        {
            cout << "Error0: " << sqlite3_errmsg(db) << endl;
        }
        else
        {
            cout << "Table Created!" << endl;
        }
    }
}

void insertTable(string id, string name, string pwd, string pos)
{

    query = "INSERT INTO hospital(id, name, pwd, pos) VALUES(?,?,?,?);";

    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, id.c_str(), id.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, pwd.c_str(), pwd.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, pos.c_str(), pos.length(), SQLITE_TRANSIENT);

    int result1 = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    if (result1 != SQLITE_DONE)
    {
        cout << "Error executing DELETE statement: " << sqlite3_errmsg(db) << endl;
    };

    if (result != SQLITE_OK)
    {
        cout << "Error1: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        sqlite3_close(db);
        cout << "Data Added!" << endl;
    }
}

void deleteTable(string id)
{
    query = "DELETE FROM hospital WHERE id=?";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, id.c_str(), id.length(), SQLITE_TRANSIENT);
    int result1 = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    if (result1 != SQLITE_DONE)
    {
        cout << "Error executing DELETE statement: " << sqlite3_errmsg(db) << endl;
    }

    if (result != SQLITE_OK)
    {
        cout << "Error2: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        sqlite3_close(db);
        cout << "Data Deleted!" << endl;
    }
}

string stringlower(string convert)
{
    for (int i = 0; i < convert.length(); i++)
    {
        convert[i] = tolower(convert[i]);
    }
    return convert;
}

int checkAdminPwd(string name, string pwd)
{
    int totalData = 0, i = 0;
    bool okay = false;

    query = "SELECT * FROM hospital";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        totalData = totalData + 1;
    }

    Data data[totalData];
    string str, str2, str3;

    int isAdmin = 0; // Assuming not an admin by default

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 1);
        str = reinterpret_cast<const char *>(change);
        data[i].name = str;

        const unsigned char *change1 = sqlite3_column_text(stmt, 2);
        str2 = reinterpret_cast<const char *>(change1);
        data[i].pwd = str2;

        const unsigned char *change2 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change2);
        data[i].pos = str3;

        if (stringlower(str3) == "admin")
        {
            isAdmin = 1;
        }

        if (str == name && str2 == pwd && stringlower(str3) == "admin")
        {
            globalName = str;
            okay = true;
        }
        i++;
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    
    if (isAdmin != 1)
    {
        return 1;
    }

    if(okay)
    {
        return 0;
    }

    return 2; // No matching credentials found
}
