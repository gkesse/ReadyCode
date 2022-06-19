//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
//===============================================
GObject::GObject() {

}
//===============================================
GObject::~GObject() {

}
//===============================================
std::string GObject::getItem(const std::string& _code, const std::string& _data) const {
    m_dom->queryXPath(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _data.c_str()));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GObject::getItem(const std::string& _code, const std::string& _key, int _index) {
    m_dom->queryXPath(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]/%s", _code.c_str(), _index + 1, _key.c_str()));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GObject::countItem(const std::string& _code, const std::string& _key) {
    m_dom->queryXPath(sformat("/rdv/datas/data[code='%s']/map/data/%s", _code.c_str(), _key.c_str()));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
std::shared_ptr<GError>& GObject::getErrors() {
    return m_errors;
}
//===============================================
bool GObject::clearMap() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GObject* lObj = m_map.at(i);
        delete lObj;
    }
    return true;
}
//===============================================
std::string GObject::serialize(const std::string& _code) const {return "";}
//===============================================
