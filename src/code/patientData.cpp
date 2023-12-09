#include "sqlite3.h"
#include <iostream>
#include "functions.h"
#include "globals.h"

using namespace std;

sqlite3 *pdb;
sqlite3_stmt *pstmt;
int presult;
string pquery;

void makePatient()
{

    if (sqlite3_open("patient.db", &db) == SQLITE_OK)
    {

        query = "CREATE TABLE IF NOT EXISTS patient(id VARCHAR(10), name varchar(30), pwd varchar(20), meds varchar(50));";

        result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
        int result1 = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result1 != SQLITE_DONE)
        {
            cout << "Error executing MAKE statement: " << sqlite3_errmsg(db) << endl;
        }
        if (result != SQLITE_OK)
        {
            cout << "Error: " << sqlite3_errmsg(db) << endl;
        }
        else
        {
            cout << "Table Created!" << endl;
        }
    }
}

void insertPatient(string id, string name, string pwd)
{

    query = "INSERT INTO patient(id, name, pwd, meds) VALUES(?,?,?,?);";

    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, id.c_str(), id.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, pwd.c_str(), pwd.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, "", 0, SQLITE_TRANSIENT);

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

void deletePatient(string id)
{
    query = "DELETE FROM patient WHERE id=?";
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

void getpId(string id, string &name, string &pwd, string &meds);

void updatePatient(string id, string name, string pwd, string meds)
{
    getpId(id, name, pwd, meds);

    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

    query = "UPDATE patient SET name = ?, pwd = ?, meds = ? WHERE id=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pwd.c_str(), pwd.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, meds.c_str(), meds.length(), SQLITE_TRANSIENT);
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

void getpId(string id, string &name, string &pwd, string &meds)
{
    query = "SELECT * FROM patient";

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
            if (meds == "")
            {
                meds = str3;
            }
        }
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
}
