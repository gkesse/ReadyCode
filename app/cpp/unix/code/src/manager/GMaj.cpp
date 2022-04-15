//===============================================
#include "GMaj.h"
#include "GMySQL.h"
#include "GFormat.h"
#include "GString.h"
#include "GError.h"
#include "GLog.h"
#include "GShell.h"
//===============================================
GMaj::GMaj() : GObject() {
    m_id = 0;
    m_code = "";
    m_filename = "";
    m_errors.reset(new GError);
}
//===============================================
GMaj::GMaj(const std::string& _filename) : GObject() {
    m_id = 0;
    m_code = "";
    m_filename = _filename;
    m_errors.reset(new GError);
}
//===============================================
GMaj::~GMaj() {

}
//===============================================
GMaj& GMaj::createObj() {
    createDB();
    return *this;
}
//===============================================
GMaj& GMaj::loadObj() {
    loadCode();
    loadId();
    return *this;
}
//===============================================
GMaj& GMaj::saveObj() {
    if(!hasData()) {
        insertData();
    }
    else {
        updateData();
    }
    return *this;
}
//===============================================
GMaj& GMaj::createDB() {
    runMaj("$GPROJECT_DATA/mysql/pkg/pkg_maj.sh");
    return *this;
}
//===============================================
GMaj& GMaj::loadCode() {
    m_code = GString(m_filename).splitData('-').at(0);
    GLOGT(eGINF, "m_code.......: %s", m_code.c_str());
    GLOGT(eGINF, "m_filename...: %s", m_filename.c_str());
    return *this;
}
//===============================================
GMaj& GMaj::loadId() {
    std::string lId = GMySQL().readData(sformat(""
            " select _id "
            " from maj"
            " where _code = '%s' "
            "", m_code.c_str()));
    if(lId != "") m_id = std::stoi(lId);
    GLOGT(eGINF, "m_id.........: %d", m_id);
    return *this;
}
//===============================================
bool GMaj::hasData() const {
    return (m_id != 0);
}
//===============================================
GMaj& GMaj::insertData() {
    GMySQL().execQuery(sformat(""
            " insert into maj"
            " ( _code, _filename ) "
            " values ( '%s', '%s' ) "
            "", m_code.c_str()
            , m_filename.c_str()));
    return *this;
}
//===============================================
GMaj& GMaj::updateData() {
    GMySQL().execQuery(sformat(""
            " update maj "
            " set _code = '%s' "
            " , _filename = '%s' "
            " where _id = %d "
            "", m_code.c_str()
            , m_filename.c_str()
            , m_id));
    return *this;
}
//===============================================
GMaj& GMaj::runMaj(const std::string& _filename) {
    std::string lDatabase = GMySQL().loadDatabase();
    std::string lCommand = sformat(""
            " %s %s \n"
            "", _filename.c_str()
            , lDatabase.c_str());
    GShell().runSystem(lCommand);
    GLOGT(eGINF, "command......:%s", lCommand.c_str());
    return *this;
}
//===============================================
