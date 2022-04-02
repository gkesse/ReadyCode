//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GError.h"
//===============================================
GObject::GObject() {
    m_errors.reset(new GError);
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
std::shared_ptr<GError>& GObject::getErrors() {
    return m_errors;
}
//===============================================
