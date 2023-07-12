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
void GObject::loadFromMap(int i) {
    if(i >= 1 && i <= size()) {
        GObject* lObj = m_map[i - 1];
        setObj(*lObj);
    }
}
//===============================================
void GObject::loadToMap(int i) {
    if(i >= 1 && i <= size()) {
        GObject* lObj = m_map[i - 1];
        lObj->setObj(*this);
    }
}
//===============================================
const GLog& GObject::getLogs() const {
    return m_logs;
}
//===============================================
int GObject::size() const {
    return (int)m_map.size();
}
//===============================================
GString GObject::getEnv(const GString& _env, const GString& _defaultValue) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return _defaultValue;
    return lEnv;
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
void GObject::setObj(const GObject& _obj) {}
GString GObject::serialize(const GString& _code) const {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
