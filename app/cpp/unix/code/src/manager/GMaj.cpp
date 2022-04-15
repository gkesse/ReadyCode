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
void GMaj::loadObj() {
    loadCode();
    loadId();
}
//===============================================
void GMaj::loadCode() {
    GLOGT(eGINF, "");
    m_code = GString(m_filename).splitData('-').at(0);
    GLOGW(eGINF, "m_code......: %s", m_code.c_str());
    GLOGW(eGINF, "m_filename..: %s", m_filename.c_str());
}
//===============================================
void GMaj::loadId() {
    GLOGT(eGINF, "");
    m_id = std::stoi(GMySQL().readData(sformat(""
            " select _id "
            " from maj"
            " where _code = '%s' "
            "", m_code.c_str())));
    GLOGW(eGINF, "m_id........: %d", m_id);
}
//===============================================
bool GMaj::hasData() const {
    return (m_id != 0);
}
//===============================================
void GMaj::insertData(const GMaj& _data) {
    GMySQL().execQuery(sformat(""
            " insert into maj"
            " ( _code, _filename ) "
            " values ( '%s', '%s' ) "
            "", _data.m_code.c_str()
            , _data.m_filename.c_str()));
}
//===============================================
void GMaj::updateData(const GMaj& _data) {
    GMySQL().execQuery(sformat(""
            " update maj "
            " set _code = '%s' "
            " , _filename = '%s' "
            " where _id = %d"
            "", _data.m_id
            , _data.m_code.c_str(),
            _data.m_filename.c_str()));
}
//===============================================
