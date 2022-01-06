//===============================================
#ifndef _GSQLite_
#define _GSQLite_
//===============================================
#include "GObject.h"
//===============================================
#define GSQLITE GSQLite::Instance()
//===============================================
class GSQLite : public GObject {
public:
    typedef int (*onExecCB)(void* _params, int _colCount, char** _colVals, char** _colNames);

public:
    GSQLite(bool _init = true);
    ~GSQLite();
    static GSQLite* Instance();
    void createDoms();
    bool getVersionShow() const;
    std::string getVersion() const;
    bool openDatabase(const std::string& _filename);
    bool executeQuery(const std::string& _query, onExecCB _onExec = 0, void* _params = 0);
    bool prepareQuery(const std::string& _query);
    bool stepQuery();
    std::string getColumnData(int _col) const;
    void finalizeQuery();
    void closeDatabase();
    void writeData(const char* _query, ...);
    std::string readData(const char* _query, ...);
    std::vector<std::string> readRow(const char* _query, ...);
    std::vector<std::string> readCol(const char* _query, ...);
    std::vector<std::vector<std::string>> readMap(const char* _query, ...);
    static int onReadData(void* _params, int _colCount, char** _colVals, char** _colNames);
    static int onReadRow(void* _params, int _colCount, char** _colVals, char** _colNames);
    static int onReadCol(void* _params, int _colCount, char** _colVals, char** _colNames);
    static int onReadMap(void* _params, int _colCount, char** _colVals, char** _colNames);

private:
    static const int BUFFER_SIZE = 256;

private:
    static GSQLite* m_instance;
    sqlite3* m_sqlite3;
    sqlite3_stmt* m_stmt;
    char m_buffer[BUFFER_SIZE + 1];
    int m_rowCount;
    std::string m_dataVal;
    std::vector<std::string> m_dataList;
    std::vector<std::vector<std::string>> m_dataMap;
    bool m_namesOn;
    std::vector<std::string> m_names;
};
//==============================================
#endif
//==============================================
