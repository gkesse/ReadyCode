//===============================================
#include "GSQLite.h"
#include "GStruct.h"
//===============================================
GSQLite* GSQLite::m_instance = 0;
//===============================================
GSQLite::GSQLite() {
    m_sqlite3 = 0;
    m_stmt = 0;
}
//===============================================
GSQLite::~GSQLite() {
    finalizeQuery();
    closeDatabase();
}
//===============================================
GSQLite* GSQLite::Instance() {
    if(m_instance == 0) {
        m_instance = new GSQLite;
        m_instance->openDatabase("database.dat");
    }
    return m_instance;
}
//===============================================
void GSQLite::getVersion(std::string& _version) {
    _version = sqlite3_libversion();
}
//===============================================
void GSQLite::openDatabase(const std::string& _filename) {
    sqlite3_open(_filename.c_str(), &m_sqlite3);
}
//===============================================
void GSQLite::executeQuery(const std::string& _query, onExecCB _onExec, void* _params) {
    char* lError;
    sqlite3_exec(m_sqlite3, _query.c_str(), _onExec, _params, &lError);
}
//===============================================
void GSQLite::prepareQuery(const std::string& _query) {
    sqlite3_prepare_v2(m_sqlite3, _query.c_str(), -1, &m_stmt, 0);
}
//===============================================
void GSQLite::stepQuery() {
    sqlite3_step(m_stmt);
}
//===============================================
void GSQLite::getColumnData(std::string& _data, int _col) {
    _data = (char*)sqlite3_column_text(m_stmt, _col);
}
//===============================================
void GSQLite::finalizeQuery() {
    sqlite3_finalize(m_stmt);
}
//===============================================
void GSQLite::closeDatabase() {
    sqlite3_close(m_sqlite3);
}
//===============================================
void GSQLite::writeData(const std::string& _query) {
    executeQuery(_query, 0, 0);
}
//===============================================
std::string GSQLite::readData(const std::string& _query, std::vector<std::string>* _names) {
    sGSQLite lParams;
    lParams.names = _names;
    executeQuery(_query, onReadData, &lParams);
    return lParams.data_val;
}
//===============================================
std::vector<std::string> GSQLite::readRow(const std::string& _query, std::vector<std::string>* _names) {
    sGSQLite lParams;
    lParams.names = _names;
    executeQuery(_query, onReadRow, &lParams);
    return lParams.data_list;
}
//===============================================
std::vector<std::string> GSQLite::readCol(const std::string& _query, std::vector<std::string>* _names) {
    sGSQLite lParams;
    lParams.names = _names;
    executeQuery(_query, onReadCol, &lParams);
    return lParams.data_list;
}
//===============================================
std::vector<std::vector<std::string>> GSQLite::readMap(const std::string& _query, std::vector<std::string>* _names) {
    sGSQLite lParams;
    lParams.names = _names;
    executeQuery(_query, onReadMap, &lParams);
    return lParams.data_map;
}
//===============================================
int GSQLite::onReadData(void* _params, int _colCount, char** _colVals, char** _colNames) {
    sGSQLite* lParams = (sGSQLite*)_params;
    if(lParams->row_count == 0) {
        if(lParams->names && lParams->names_on) {
            lParams->names->push_back(_colNames[0]);
        }
        lParams->data_val = _colVals[0];
        lParams->names_on = false;
        lParams->row_count++;
    }
    return 0;
}
//===============================================
int GSQLite::onReadRow(void* _params, int _colCount, char** _colVals, char** _colNames) {
    sGSQLite* lParams = (sGSQLite*)_params;
    if(lParams->row_count == 0) {
        for(int i = 0; i < _colCount; i++) {
            if(lParams->names && lParams->names_on) {
                lParams->names->push_back(_colNames[i]);
            }
            lParams->data_list.push_back(_colVals[i]);
        }
        lParams->names_on = false;
        lParams->row_count++;
    }
    return 0;
}
//===============================================
int GSQLite::onReadCol(void* _params, int _colCount, char** _colVals, char** _colNames) {
    sGSQLite* lParams = (sGSQLite*)_params;
    if(lParams->names && lParams->names_on) {
        lParams->names->push_back(_colNames[0]);
    }
    lParams->data_list.push_back(_colVals[0]);
    lParams->names_on = false;
    lParams->row_count++;
    return 0;
}
//===============================================
int GSQLite::onReadMap(void* _params, int _colCount, char** _colVals, char** _colNames) {
    sGSQLite* lParams = (sGSQLite*)_params;
    std::vector<std::string> lData;
    for(int i = 0; i < _colCount; i++) {
        if(lParams->names && lParams->names_on) {
            lParams->names->push_back(_colNames[i]);
        }
        lData.push_back(_colVals[i]);
    }
    lParams->names_on = false;
    lParams->data_map.push_back(lData);
    lParams->row_count++;
    return 0;
}
//===============================================
