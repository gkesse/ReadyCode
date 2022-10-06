//===============================================
#include "GFile.h"
#include "GDate.h"
#include "GShell.h"
#include "GEnv.h"
#include "GCode.h"
#include "GClient.h"
//===============================================
GFile::GFile()
: GManager() {
    m_id = 0;
}
//===============================================
GFile::GFile(const GString& _fullname)
: GManager() {
    m_id = 0;
    m_fullname = _fullname;
}
//===============================================
GFile::~GFile() {

}
//===============================================
GString GFile::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "filename", m_filename);
    lDom.addData(_code, "content", m_content, true);
    return lDom.toString();
}
//===============================================
bool GFile::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_filename = lDom.getData(_code, "filename");
    m_content = lDom.getData(_code, "content");
    return true;
}
//===============================================
void GFile::setId(int _id) {
    m_id = _id;
}
//===============================================
void GFile::setFilename(const GString& _filename) {
    m_filename = _filename;
}
//===============================================
void GFile::setContent(const GString& _content) {
    m_content = _content;
}
//===============================================
GString GFile::getContent() const {
    return m_content;
}
//===============================================
void GFile::setFullname(const GString& _fullname) {
    m_fullname = _fullname;
}
//===============================================
bool GFile::existFile() const {
    if(m_fullname == "") return false;
    std::ifstream lFile(m_fullname.data());
    return lFile.good();
}
//===============================================
GString GFile::getContents() const {
    if(m_fullname == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_fullname.data());
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str().c_str();
}
//===============================================
GString GFile::getContentBin() const {
    if(m_fullname == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_fullname.c_str(), std::ios::in | std::ios::binary);
    std::vector<char> lData = std::vector<char>(std::istreambuf_iterator<char>(lFile), std::istreambuf_iterator<char>());
    return lData;
}
//===============================================
void GFile::setContents(const GString& _data) {
    if(m_fullname == "") return;
    std::ofstream lFile(m_fullname.c_str());
    lFile << _data.c_str();
}
//===============================================
void GFile::setContentBin(const GString& _data) {
    if(m_fullname == "") return;
    std::ofstream lFile(m_fullname.c_str(), std::ios::out | std::ios::binary);
    lFile.write(_data.data(), _data.size());
}
//===============================================
void GFile::saveFile() {
    GString lData = serialize();
    lData = GCALL_SERVER("file", "save_file", lData);
    deserialize(lData);
}
//===============================================
void GFile::downloadFile() {
    GString lData = serialize();
    lData = GCALL_SERVER("file", "download_file", lData);
    deserialize(lData);
}
//===============================================
