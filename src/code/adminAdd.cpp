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
        cout << "Error executing ADD statement: " << sqlite3_errmsg(db) << endl;
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
    bool okay = false;

    query = "SELECT * FROM hospital";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string str, str2, str3;

    int isAdmin = 0; // Assuming not an admin by default

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 1);
        str = reinterpret_cast<const char *>(change);

        const unsigned char *change1 = sqlite3_column_text(stmt, 2);
        str2 = reinterpret_cast<const char *>(change1);

        const unsigned char *change2 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change2);

        if (stringlower(str3) == "admin")
        {
            isAdmin = 1;
        }

        if (str == name && str2 == pwd && stringlower(str3) == "admin")
        {
            globalName = str;
            okay = true;
        }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    if (isAdmin != 1)
    {
        return 1;
    }

    if (okay)
    {
        return 0;
    }

    return 2; // No matching credentials found
}

void getId(string id, string &name, string &pwd, string &pos);

void updateTable(string id, string name, string pwd, string pos)
{
    getId(id, name, pwd, pos);

    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

    query = "UPDATE hospital SET name = ?, pwd = ?, pos = ? WHERE id=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pwd.c_str(), pwd.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, pos.c_str(), pos.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, id.c_str(), id.length(), SQLITE_TRANSIENT);

    int result1 = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    if (result1 != SQLITE_DONE)
    {
        cout << "Error executing UPDATE statement: " << sqlite3_errmsg(db) << endl;
    }

    if (result != SQLITE_OK)
    {
        cout << "Error2: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        sqlite3_close(db);
        cout << "Data Updated!" << endl;
    }
}

void getId(string id, string &name, string &pwd, string &pos)
{
    query = "SELECT * FROM hospital";

    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
    }

    string str, str1, str2, str3;

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 0);
        str = reinterpret_cast<const char *>(change);

        const unsigned char *change1 = sqlite3_column_text(stmt, 1);
        str1 = reinterpret_cast<const char *>(change1);

        const unsigned char *change2 = sqlite3_column_text(stmt, 2);
        str2 = reinterpret_cast<const char *>(change2);

        const unsigned char *change3 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change3);

        if (str == id)
        {
            if (name == "")
            {
                name = str1;
            }
            if (pwd == "")
            {
                pwd = str2;
            }
            if (pos == "")
            {
                pos = str3;
            }
        }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
}

int checkDocPwd(string name, string pwd)
{

    bool okay = false;

    query = "SELECT * FROM hospital";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string str, str2, str3;

    int isDoctor = 0; // Assuming not an admin by default

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 1);
        str = reinterpret_cast<const char *>(change);

        const unsigned char *change1 = sqlite3_column_text(stmt, 2);
        str2 = reinterpret_cast<const char *>(change1);

        const unsigned char *change2 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change2);

        if (stringlower(str3) == "doctor")
        {
            isDoctor = 1;
        }

        if (str == name && str2 == pwd && stringlower(str3) == "doctor")
        {
            globalName = str;
            okay = true;
        }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    sqlite3_close(db);

    if (isDoctor != 1)
    {
        return 1;
    }

    if (okay)
    {
        return 0;
    }

    return 2; // No matching credentials found
}

int checkRecpPwd(string name, string pwd)
{
    bool okay = false;

    query = "SELECT * FROM hospital";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string str, str2, str3;

    int isReception = 0; // Assuming not an admin by default

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 1);
        str = reinterpret_cast<const char *>(change);

        const unsigned char *change1 = sqlite3_column_text(stmt, 2);
        str2 = reinterpret_cast<const char *>(change1);

        const unsigned char *change2 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change2);

        if (stringlower(str3) == "reception")
        {
            isReception = 1;
        }

        if (str == name && str2 == pwd && stringlower(str3) == "reception")
        {
            globalName = str;
            okay = true;
        }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    sqlite3_close(db);

    if (isReception != 1)
    {
        return 1;
    }

    if (okay)
    {
        return 0;
    }

    return 2; // No matching credentials found
}

int checkPatientPwd(string name, string pwd)
{

    bool okay = false;

    query = "SELECT * FROM patient";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string str, str2, str3;

    int isReception = 0; // Assuming not an admin by default

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 1);
        str = reinterpret_cast<const char *>(change);

        const unsigned char *change1 = sqlite3_column_text(stmt, 2);
        str2 = reinterpret_cast<const char *>(change1);

        const unsigned char *change2 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change2);

        if (str == name && str2 == pwd)
        {
            globalMeds = str3;
            globalName = str;
            okay = true;
        }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    if (okay)
    {
        return 0;
    }

    return 2; // No matching credentials found
}

int checkNursePwd(string name, string pwd)
{
    bool okay = false;

    query = "SELECT * FROM hospital";
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    if (result != SQLITE_OK)
    {
        cout << "Error3: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string str, str2, str3;

    int isNurse = 0; // Assuming not an admin by default

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const unsigned char *change = sqlite3_column_text(stmt, 1);
        str = reinterpret_cast<const char *>(change);

        const unsigned char *change1 = sqlite3_column_text(stmt, 2);
        str2 = reinterpret_cast<const char *>(change1);

        const unsigned char *change2 = sqlite3_column_text(stmt, 3);
        str3 = reinterpret_cast<const char *>(change2);

        if (stringlower(str3) == "nurse")
        {
            isNurse = 1;
        }

        if (str == name && str2 == pwd && stringlower(str3) == "nurse")
        {
            globalName = str;
            okay = true;
        }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    if (isNurse != 1)
    {
        return 1;
    }

    if (okay)
    {
        return 0;
    }

    return 2; // No matching credentials found
}