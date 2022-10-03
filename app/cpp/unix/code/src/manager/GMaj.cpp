//===============================================
#include "GMaj.h"
#include "GMySQL.h"
#include "GString.h"
#include "GLog.h"
#include "GShell.h"
#include "GEnv.h"
#include "GSocket.h"
#include "GCode.h"
#include "GThread.h"
#include "GPath.h"
#include "GDir.h"
#include "GAsync.h"
//===============================================
GMaj::GMaj() : GModule() {
    m_id = 0;
    m_code = "";
    m_path = "";
    m_filename = "";
}
//===============================================
GMaj::GMaj(const GString& _path, const GString& _filename) : GModule() {
    m_id = 0;
    m_code = "";
    m_path = _path;
    m_filename = _filename;
}
//===============================================
GMaj::~GMaj() {

}
//===============================================
GString GMaj::serialize(const GString& _code) const {
    GCode lReq;
    lReq.createDoc();
    lReq.addData(_code, "id", m_id);
    lReq.addData(_code, "code", m_code);
    lReq.addData(_code, "path", m_path);
    lReq.addData(_code, "filename", m_filename);
    return lReq.toStringCode(_code);
}
//===============================================
void GMaj::deserialize(const GString& _req, const GString& _code) {
    GModule::deserialize(_req);
    GCode lReq;
    lReq.loadXml(_req);
    m_id = GString(lReq.getData(_code, "id")).toInt();
    m_code = lReq.getData(_code, "code");
    m_path = lReq.getData(_code, "path");
    m_filename = lReq.getData(_code, "filename");
}
//===============================================
void GMaj::onModule(GSocket* _client) {
    deserialize(_client->toReq());
    //===============================================
    // method
    //===============================================
    if(m_method == "update_database") {
        onUpdateDatabase(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onMethodUnknown(_client);
    }
}
//===============================================
void GMaj::onUpdateDatabase(GSocket* _client) {
    GAsync* lAsync = new GAsync;
    lAsync->setClient(_client);
    lAsync->deserialize(_client->toReq());
    lAsync->setTitle("Maj base de données");
    lAsync->exec((void*)onUpdateDatabaseThread, lAsync);
}
//===============================================
void GMaj::onUpdateDatabaseThread(void* _params) {
    std::shared_ptr<GAsync> lAsync((GAsync*)_params);
    GSocket* lClient = lAsync->getClient();
    GString lPath = GPATH("mysql", "maj");
    std::vector<GString> lFiles = GDir().openDir(lPath, false, false);

    GLOGT(eGMSG, "%s\n", GSTRC(lFiles));

    for(int i = 0; i < (int)lFiles.size(); i++) {
        GString lFile = lFiles.at(i);
        GMaj lMaj(lPath, lFile);
        lMaj.createDB();
        lMaj.loadCode();
        lMaj.loadId();
        lMaj.saveData();
        lMaj.runMaj();
    }

    lAsync->finish();
    GString lData = lAsync->serialize();
    lClient->addResponse(lData);
}
//===============================================
void GMaj::createDB() {
    createDB(GEnv().isTestEnv());
}
//===============================================
void GMaj::createDB(bool _isTestEnv) {
    runMaj("$GPROJECT_DATA/mysql/pkg/pkg_maj.sh", _isTestEnv);
}
//===============================================
void GMaj::loadCode() {
    if(m_filename == "") return;
    m_code = GString(m_filename).extract(0, "-");
    GLOGT(eGMSG, "%s : %s", m_code.c_str(), m_filename.c_str());
}
//===============================================
void GMaj::loadId() {
    loadId(GEnv().isTestEnv());
}
//===============================================
void GMaj::loadId(bool _isTestEnv) {
    if(m_code == "") return;

    GString lId = GMySQL().readData(GFORMAT(""
            " select _id "
            " from maj "
            " where _code = '%s' "
            "", m_code.c_str()
    ), _isTestEnv);

    m_id = GString(lId).toInt();

    GLOGT(eGMSG, "%d", m_id);
}
//===============================================
void GMaj::saveData() {
    saveData(GEnv().isTestEnv());
}
//===============================================
void GMaj::saveData(bool _isTestEnv) {
    if(!m_id) {
        insertData(_isTestEnv);
    }
}
//===============================================
void GMaj::insertData(bool _isTestEnv) {
    if(m_code == "") return;
    if(m_filename == "") return;

    GMySQL().execQuery(GFORMAT(""
            " insert into maj "
            " ( _code, _filename ) "
            " values ( '%s', '%s' ) "
            "", m_code.c_str()
            , m_filename.c_str()
    ), _isTestEnv);
}
//===============================================
void GMaj::updateData(bool _isTestEnv) {
    if(!m_id) return;
    if(m_code == "") return;
    if(m_filename == "") return;

    GMySQL().execQuery(GFORMAT(""
            " update maj "
            " set _code = '%s' "
            " , _filename = '%s' "
            " where _id = %d "
            "", m_code.c_str()
            , m_filename.c_str()
            , m_id
    ), _isTestEnv);
}
//===============================================
void GMaj::runMaj() {
    runMaj(GEnv().isTestEnv());
}
//===============================================
void GMaj::runMaj(bool _isTestEnv) {
    if(!m_id) {
        GString lFilename = GFORMAT("%s/%s"
                , m_path.c_str()
                , m_filename.c_str());
        runMaj(lFilename, _isTestEnv);
    }
}
//===============================================
void GMaj::runMaj(const GString& _filename, bool _isTestEnv) {
    if(_filename == "") return;
    GString lDatabase = GMySQL().loadDatabase(_isTestEnv);
    GString lCommand = GFORMAT(""
            " chmod a+x %s \n"
            " %s %s \n"
            "", _filename.c_str()
            , _filename.c_str()
            , lDatabase.c_str());
    GShell().runSystem(lCommand);
}
//===============================================
