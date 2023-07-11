//===============================================
#include "GObject.h"
//===============================================
GObject::GObject() {
    m_resp.createDoc();
    m_resp.createDatas();
}
//===============================================
GObject::~GObject() {
    clearMap();
}
//===============================================
void GObject::clearMap() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GObject* lObj = m_map[i];
        delete lObj;
    }
    m_map.clear();
    m_logs.clearMap();
    m_dataLogs.clearMap();
}
//===============================================
const GLog& GObject::getLogs() const {
    return m_logs;
}
//===============================================
const GLog& GObject::getDataLogs() const {
    return m_dataLogs;
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code) const {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
