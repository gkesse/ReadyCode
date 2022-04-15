//===============================================
#include "GMaj.h"
#include "GMySQL.h"
#include "GFormat.h"
#include "GString.h"
#include "GError.h"
#include "GLog.h"
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
GMaj& GMaj::loadCode() {
    GLOGT(eGINF, "");
    m_code = GString(m_filename).splitData('-').at(0);
    GLOGW(eGINF, "m_code.......: %s", m_code.c_str());
    GLOGW(eGINF, "m_filename...: %s", m_filename.c_str());
    return *this;
}
//===============================================
GMaj& GMaj::loadId() {
    GLOGT(eGINF, "");
    std::string lId = GMySQL().readData(sformat(""
            " select _id "
            " from maj"
            " where _code = '%s' "
            "", m_code.c_str()));
    if(lId != "") m_id = std::stoi(lId);
    GLOGW(eGINF, "m_id.........: %d", m_id);
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
            " where _id = %d"
            "", m_id
            , m_code.c_str(),
            m_filename.c_str()));
    return *this;
}
//===============================================
