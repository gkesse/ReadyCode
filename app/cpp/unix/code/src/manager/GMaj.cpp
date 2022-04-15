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
void GMaj::loadCode() {
    GLOGT(eGINF, "");
    m_code = GString(m_filename).splitData('-').at(0);
    GLOGW(eGINF, "%s", m_code.c_str());
    GLOGW(eGINF, "%s", m_filename.c_str());
}
//===============================================
int GMaj::getId(const std::string& _code) const {
    GMySQL lMySQL;
    int lId = std::stoi(lMySQL.readData(sformat(""
            " select _id "
            " from maj"
            " where _code = '%s' "
            "", _code.c_str())));
    return lId;
}
//===============================================
bool GMaj::hasData(const std::string& _code) const {
    return (getId(_code) > 0);
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
