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
