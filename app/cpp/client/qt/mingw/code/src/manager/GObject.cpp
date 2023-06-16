//===============================================
#include "GObject.h"
//===============================================
GObject::GObject() {
    m_resp.createDoc();
    m_resp.createDatas();
}
//===============================================
GObject::~GObject() {
    clear();
}
//===============================================
void GObject::clear() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GObject* lObj = m_map[i];
        delete lObj;
    }
    m_map.clear();
}
//===============================================
const GLog& GObject::getLogs() const {
    return m_logs;
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code) const {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
