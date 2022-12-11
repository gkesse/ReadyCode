//===============================================
#include "GCss.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
//===============================================
GCss::GCss(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_tableWidget.reset(new GTableWidgetUi);
}
//===============================================
GCss::~GCss() {
    clearMap();
}
//===============================================
GObject* GCss::clone() const {
    return new GCss;
}
//===============================================
GString GCss::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "key", m_key);
    lDom.addData(_code, "filename", m_filename);
    lDom.addData(_code, m_map, this);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GCss::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_key = lDom.getData(_code, "key");
    m_filename = lDom.getData(_code, "filename");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GCss::setKey(const GString& _key) {
    m_key = _key;
}
//===============================================
void GCss::setFilename(const GString& _filename) {
    m_filename = _filename;
}
//===============================================
GString GCss::getKey() const {
    return m_key;
}
//===============================================
GString GCss::getFilename() const {
    return m_filename;
}
//===============================================
void GCss::saveCss() {
    GString lData = serialize();
    lData = GCALL_SERVER("css", "save_css", lData);
    deserialize(lData);
}
//===============================================
