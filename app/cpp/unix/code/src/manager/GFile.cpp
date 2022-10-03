//===============================================
#include "GFile.h"
#include "GShell.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GEnv.h"
#include "GLog.h"
#include "GPath.h"
#include "GBase64.h"
#include "GServer.h"
//===============================================
GFile::GFile()
: GModule() {
    m_id = 0;
}
//===============================================
GFile::GFile(const GString& _fullname)
: GModule() {
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
    GModule::deserialize(_data);
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
bool GFile::onModule() {
    deserialize(m_server->getRequest());
    if(m_method == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_method == "save_file") {
        onSaveFile();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GFile::onSaveFile() {
    if(m_id != 0) {GERROR_ADD(eGERR, "Le fichier est déjà enregistré."); return false;}
    if(m_filename == "") {GERROR_ADD(eGERR, "Le nom du fichier est obligatoire."); return false;}
    if(m_content == "") {GERROR_ADD(eGERR, "Le contenu du fichier est vide."); return false;}
    if(!saveFile()) return false;
    return true;
}
//===============================================
bool GFile::saveFile() {
    if(!insertFile()) return false;
    if(!updateFile()) return false;
    if(!saveContent()) return false;
    return true;
}
//===============================================
bool GFile::initFile() {
    m_homePath = GEnv().getEnv("HOME");
    m_filePath = GFORMAT("%s/.readydev/file", m_homePath.c_str());
    GShell().createDir(m_filePath);
    m_filePath.print();
    return true;
}
//===============================================
bool GFile::insertFile() {
    if(m_id != 0) return false;
    initFile();
    GMySQL lMySQL2;
    if(!lMySQL2.execQuery(GFORMAT(""
            " insert into _file "
            " ( _filename ) "
            " values ( '%s' ) "
            "", m_filename.c_str()
    ))) return false;
    m_id = lMySQL2.getId();
    return true;
}
//===============================================
bool GFile::updateFile() {
    if(m_id == 0) return false;
    m_fullname = GFORMAT("%s/%d_%s", m_filePath.c_str(), m_id, m_filename.c_str());
    if(!GMySQL().execQuery(GFORMAT(""
            " update _file "
            " set _fullname = '%s' "
            " where _id = %d "
            "", m_fullname.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================
bool GFile::saveContent() {
    if(m_id == 0) return false;
    GFile lFile(m_fullname);
    GString lDataBin(GBase64(m_content).decodeData());
    lFile.setContentBin(lDataBin);
    GLOG_ADD(eGLOG, "Le fichier a bien été enregistré.");
    return true;
}
//===============================================
bool GFile::downloadFile() {

    return true;
}
//===============================================
