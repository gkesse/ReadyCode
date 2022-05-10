//===============================================
#include "GMaj.h"
#include "GMySQL.h"
#include "GFormat.h"
#include "GString.h"
#include "GError.h"
#include "GLog.h"
#include "GShell.h"
#include "GEnv.h"
#include "GSocket.h"
#include "GCode.h"
#include "GThread.h"
#include "GPath.h"
#include "GDir.h"
#include "GTimer.h"
//===============================================
GMaj::GMaj() : GModule() {
    m_id = 0;
    m_code = "";
    m_path = "";
    m_filename = "";
}
//===============================================
GMaj::GMaj(const std::string& _path, const std::string& _filename) : GModule() {
    m_id = 0;
    m_code = "";
    m_path = _path;
    m_filename = _filename;
}
//===============================================
GMaj::~GMaj() {

}
//===============================================
void GMaj::onModule(GSocket* _client) {
    std::string lMethod = _client->getReq()->getMethod();
    //===============================================
    // method
    //===============================================
    if(lMethod == "update_database") {
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
    GLOGT(eGINF, "");
    GThread lThread;
    GTimer lTimer;
    lThread.createThread((void*)onUpdateDatabaseThread, _client);
    lTimer.setCallback((void*)onUpdateDatabaseTimer, 500);
    lTimer.pauseTimer();
}
//===============================================
void GMaj::onUpdateDatabaseThread(GSocket* _client) {
    GLOGT(eGFUN, "");
    std::string lPath = GRES("mysql", "maj");
    std::vector<std::string> lFiles = GDir().openDir(lPath, false, false);
    GLOGT(eGMSG, "%s\n", GSTRC(lFiles).c_str());
    for(int i = 0; i < (int)lFiles.size(); i++) {
        std::string lFile = lFiles.at(i);
        GMaj lMaj(lPath, lFile);
        lMaj.createDB();
        lMaj.loadCode();
        lMaj.loadId();
        lMaj.saveData();
        lMaj.runMaj();
    }
}
//===============================================
void GMaj::onUpdateDatabaseTimer(int _signo) {
    GLOGT(eGINF, "");
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

    m_code = GString(m_filename).splitData('-').at(0);

    GLOGT(eGOFF, ""
            "code.........: (%s)\n"
            "filename.....: (%s)\n"
            "", m_code.c_str()
            , m_filename.c_str()
    );
}
//===============================================
void GMaj::loadId() {
    loadId(GEnv().isTestEnv());
}
//===============================================
void GMaj::loadId(bool _isTestEnv) {
    if(m_code == "") return;

    std::string lId = GMySQL().readData(sformat(""
            " select _id "
            " from maj "
            " where _code = '%s' "
            "", m_code.c_str()
    ), _isTestEnv);

    m_id = GString(lId).toInt();

    GLOGT(eGOFF, "m_id.........: %d", m_id);
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

    GMySQL().execQuery(sformat(""
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

    GMySQL().execQuery(sformat(""
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
        std::string lFilename = sformat("%s/%s"
                , m_path.c_str()
                , m_filename.c_str());
        runMaj(lFilename, _isTestEnv);
    }
}
//===============================================
void GMaj::runMaj(const std::string& _filename, bool _isTestEnv) {
    if(_filename == "") return;
    std::string lDatabase = GMySQL().loadDatabase(_isTestEnv);
    std::string lCommand = sformat(""
            " chmod a+x %s \n"
            " %s %s \n"
            "", _filename.c_str()
            , _filename.c_str()
            , lDatabase.c_str());
    GShell().runSystem(lCommand);
}
//===============================================
