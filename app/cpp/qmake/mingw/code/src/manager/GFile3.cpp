//===============================================
#include "GFile3.h"
#include "GShell2.h"
#include "GEnv2.h"
#include "GDate2.h"
#include "GCode2.h"
#include "GClient.h"
//===============================================
GFile3::GFile3(QObject* _parent)
: GModule2(_parent) {
    m_id = 0;
}
//===============================================
GFile3::GFile3(const GString& _filename, QObject* _parent)
: GModule2(_parent) {
    m_id = 0;
    m_filename = _filename;
}
//===============================================
GFile3::~GFile3() {

}
//===============================================
GString GFile3::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "key", m_key);
    lDom.addData(_code, "filename", m_filename);
    lDom.addData(_code, "content", m_content);
    return lDom.toString();
}
//===============================================
bool GFile3::deserialize(const GString& _data, const GString& _code) {
    GModule2::deserialize(_data);
    GCode2 lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_key = lDom.getData(_code, "key");
    m_filename = lDom.getData(_code, "filename");
    m_content = lDom.getData(_code, "content");
    return true;
}
//===============================================
void GFile3::setKey(const GString& _key) {
    m_key = _key;
}
//===============================================
void GFile3::setFilename(const GString& _filename) {
    m_filename = _filename;
}
//===============================================
void GFile3::setContent(const GString& _content) {
    m_content = _content;
}
//===============================================
void GFile3::saveFile() {
    GString lData = serialize();
    lData = GCLIENTI->callServer("file", "save_file", lData);
    deserialize(lData);
}
//===============================================
bool GFile3::existFile() const {
    if(m_filename == "") return false;
    std::ifstream lFile(m_filename.data());
    return lFile.good();
}
//===============================================
GString GFile3::getContents() const {
    if(m_filename == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_filename.data());
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str().c_str();
}
//===============================================
void GFile3::setContents(const GString& _data) {
    if(m_filename == "") return;
    std::ofstream lFile(m_filename.data());
    lFile << _data.data();
}
//===============================================
