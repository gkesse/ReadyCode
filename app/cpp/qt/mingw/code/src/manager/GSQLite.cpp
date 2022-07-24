//===============================================
#include "GSQLite.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
GSQLite* GSQLite::m_instance = 0;
//===============================================
GSQLite::GSQLite(bool _init) : GObject() {
    m_sqlite3 = 0;
    m_stmt = 0;
    m_rowCount = 0;
    m_namesOn = true;

    if(_init) {
        createDoms();

        if(getVersionShow()) {
            printf("version sqlite : %s\n", getVersion().c_str());
        }

        openDatabase(GRES("cpp/sqlite", "database.xml"));
    }
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
    }
    return m_instance;
}
//===============================================
void GSQLite::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("cpp/xml", "sqlite.xml"));
    m_dom->createXPath();
}
//===============================================
bool GSQLite::getVersionShow() const {
    m_dom->queryXPath("/rdv/sqlite/versionshow");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
std::string GSQLite::getVersion() const {
    std::string lVersion = sqlite3_libversion();
    return lVersion;
}
//===============================================
bool GSQLite::openDatabase(const std::string& _filename) {
    int lAnswer = sqlite3_open(_filename.c_str(), &m_sqlite3);
    if(lAnswer != SQLITE_OK) {
        GERROR_ADD->addError(sformat("Erreur la methode (openDatabase) a echoue "
                "sur le fichier (%s).", _filename.c_str()));
        return false;
    }
    return true;
}
//===============================================
bool GSQLite::executeQuery(const std::string& _query, onExecCB _onExec, void* _params) {
    char* lError;
    int lAnswer = sqlite3_exec(m_sqlite3, _query.c_str(), _onExec, _params, &lError);
    if(lAnswer != SQLITE_OK) {
        GERROR_ADD->addError(sformat("Erreur la methode (executeQuery) a echoue "
                "sur la requete (%s) avec le message (%s).", _query.c_str(), lError));
        return false;
    }
    return true;
}
//===============================================
bool GSQLite::prepareQuery(const std::string& _query) {
    int lAnswer = sqlite3_prepare_v2(m_sqlite3, _query.c_str(), -1, &m_stmt, 0);
    if(lAnswer != SQLITE_OK) {
        GERROR_ADD->addError(sformat("Erreur la methode (prepareQuery) a echoue "
                "sur la requete (%s).", _query.c_str()));
        return false;
    }
    return true;
}
//===============================================
bool GSQLite::stepQuery() {
    int lAnswer = sqlite3_step(m_stmt);
    if(lAnswer != SQLITE_OK) {
        GERROR_ADD->addError("Erreur la methode (stepQuery) a echoue.");
        return false;
    }
    return true;
}
//===============================================
std::string GSQLite::getColumnData(int _col) const {
    std::string lData = (char*)sqlite3_column_text(m_stmt, _col);
    return lData;
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
std::string GSQLite::readData(const std::string& _query) {
    GSQLite lParams(false);
    executeQuery(_query, onReadData, &lParams);
    m_rowCount = lParams.m_rowCount;
    return lParams.m_dataVal;
}
//===============================================
std::vector<std::string> GSQLite::readRow(const std::string& _query) {
    GSQLite lParams(false);
    executeQuery(_query, onReadRow, &lParams);
    m_rowCount = lParams.m_rowCount;
    return lParams.m_dataList;
}
//===============================================
std::vector<std::string> GSQLite::readCol(const std::string& _query) {
    GSQLite lParams(false);
    executeQuery(_query, onReadCol, &lParams);
    m_rowCount = lParams.m_rowCount;
    return lParams.m_dataList;
}
//===============================================
std::vector<std::vector<std::string>> GSQLite::readMap(const std::string& _query) {
    GSQLite lParams(false);
    executeQuery(_query, onReadMap, &lParams);
    m_rowCount = lParams.m_rowCount;
    return lParams.m_dataMap;
}
//===============================================
int GSQLite::onReadData(void* _params, int _colCount, char** _colVals, char** _colNames) {
    GSQLite* lParams = (GSQLite*)_params;
    if(lParams->m_rowCount == 0) {
        if(lParams->m_namesOn) {
            lParams->m_names.push_back(_colNames[0]);
        }
        lParams->m_dataVal = _colVals[0];
        lParams->m_namesOn = false;
        lParams->m_rowCount++;
    }
    return 0;
}
//===============================================
int GSQLite::onReadRow(void* _params, int _colCount, char** _colVals, char** _colNames) {
    GSQLite* lParams = (GSQLite*)_params;
    if(lParams->m_rowCount == 0) {
        for(int i = 0; i < _colCount; i++) {
            if(lParams->m_namesOn) {
                lParams->m_names.push_back(_colNames[i]);
            }
            lParams->m_dataList.push_back(_colVals[i]);
        }
        lParams->m_namesOn = false;
        lParams->m_rowCount++;
    }
    return 0;
}
//===============================================
int GSQLite::onReadCol(void* _params, int _colCount, char** _colVals, char** _colNames) {
    GSQLite* lParams = (GSQLite*)_params;
    if(lParams->m_namesOn) {
        lParams->m_names.push_back(_colNames[0]);
    }
    lParams->m_dataList.push_back(_colVals[0]);
    lParams->m_namesOn = false;
    lParams->m_rowCount++;
    return 0;
}
//===============================================
int GSQLite::onReadMap(void* _params, int _colCount, char** _colVals, char** _colNames) {
    GSQLite* lParams = (GSQLite*)_params;
    std::vector<std::string> lData;
    for(int i = 0; i < _colCount; i++) {
        if(lParams->m_namesOn) {
            lParams->m_names.push_back(_colNames[i]);
        }
        lData.push_back(_colVals[i]);
    }
    lParams->m_namesOn = false;
    lParams->m_dataMap.push_back(lData);
    lParams->m_rowCount++;
    return 0;
}
//===============================================
