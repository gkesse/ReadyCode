//===============================================
#ifndef _GSQLite_
#define _GSQLite_
//===============================================
#include "GInclude.h"
//===============================================
#define GSQLITE GSQLite::Instance()
//===============================================
class GSQLite {
public:
    typedef int (*onExecCB)(void* _params, int _colCount, char** _colVals, char** _colNames);

public:
    GSQLite();
    ~GSQLite();
    static GSQLite* Instance();
    void getVersion(std::string& _version);
    void openDatabase(const std::string& _filename);
    void executeQuery(const std::string& _query, onExecCB _onExec = 0, void* _params = 0);
    void prepareQuery(const std::string& _query);
    void stepQuery();
    void getColumnData(std::string& _data, int _col);
    void finalizeQuery();
    void closeDatabase();
    void writeData(const std::string& _query);
    std::string readData(const std::string& _query, std::vector<std::string>* _names = 0);
    std::vector<std::string> readRow(const std::string& _query, std::vector<std::string>* _names = 0);
    std::vector<std::string> readCol(const std::string& _query, std::vector<std::string>* _names = 0);
    std::vector<std::vector<std::string>> readMap(const std::string& _query, std::vector<std::string>* _names = 0);
    static int onReadData(void* _params, int _colCount, char** _colVals, char** _colNames);
    static int onReadRow(void* _params, int _colCount, char** _colVals, char** _colNames);
    static int onReadCol(void* _params, int _colCount, char** _colVals, char** _colNames);
    static int onReadMap(void* _params, int _colCount, char** _colVals, char** _colNames);

private:
    static GSQLite* m_instance;
    sqlite3* m_sqlite3;
    sqlite3_stmt* m_stmt;
};
//==============================================
#endif
//==============================================
