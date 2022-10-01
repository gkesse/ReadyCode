//===============================================
#include "GFile3.h"
#include "GLog.h"
#include "GPath.h"
#include "GShell2.h"
#include "GEnv2.h"
#include "GCode2.h"
#include "GBase64.h"
#include "GServer.h"
#include "GMySQL2.h"
//===============================================
GFile3::GFile3()
: GModule2() {
    m_id = 0;
}
//===============================================
GFile3::GFile3(const GString& _fullname)
: GModule2() {
    m_id = 0;
    m_fullname = _fullname;
}
//===============================================
GFile3::~GFile3() {

}
//===============================================
GString GFile3::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "filename", m_filename);
    lDom.addData(_code, "content", m_content, true);
    return lDom.toString();
}
//===============================================
bool GFile3::deserialize(const GString& _data, const GString& _code) {
    GModule2::deserialize(_data);
    GCode2 lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_filename = lDom.getData(_code, "filename");
    m_content = lDom.getData(_code, "content");
    return true;
}
//===============================================
void GFile3::setId(int _id) {
    m_id = _id;
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
GString GFile3::getContent() const {
    return m_content;
}
//===============================================
void GFile3::setFullname(const GString& _fullname) {
    m_fullname = _fullname;
}
//===============================================
bool GFile3::existFile() const {
    if(m_fullname == "") return false;
    std::ifstream lFile(m_fullname.data());
    return lFile.good();
}
//===============================================
GString GFile3::getContents() const {
    if(m_fullname == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_fullname.data());
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str().c_str();
}
//===============================================
GString GFile3::getContentBin() const {
    if(m_fullname == "") return "";
    if(!existFile()) return "";
    std::ifstream lFile(m_fullname.c_str(), std::ios::in | std::ios::binary);
    std::vector<char> lData = std::vector<char>(std::istreambuf_iterator<char>(lFile), std::istreambuf_iterator<char>());
    return lData;
}
//===============================================
void GFile3::setContents(const GString& _data) {
    if(m_fullname == "") return;
    std::ofstream lFile(m_fullname.c_str());
    lFile << _data.c_str();
}
//===============================================
void GFile3::setContentBin(const GString& _data) {
    if(m_fullname == "") return;
    std::ofstream lFile(m_fullname.c_str(), std::ios::out | std::ios::binary);
    lFile.write(_data.data(), _data.size());
}
//===============================================
bool GFile3::onModule() {
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
bool GFile3::onSaveFile() {
    if(m_id != 0) {GERROR_ADD(eGERR, "Le fichier est déjà enregistré."); return false;}
    if(m_filename == "") {GERROR_ADD(eGERR, "Le nom du fichier est obligatoire."); return false;}
    if(m_content == "") {GERROR_ADD(eGERR, "Le contenu du fichier est vide."); return false;}
    if(!saveFile()) return false;
    return true;
}
//===============================================
bool GFile3::saveFile() {
    if(!insertFile()) return false;
    if(!updateFile()) return false;
    if(!saveContent()) return false;
    return true;
}
//===============================================
bool GFile3::initFile() {
    m_rootPath = "/usr/local/share/readydev/file";
    GShell2().createDir(m_rootPath);
    return true;
}
//===============================================
bool GFile3::insertFile() {
    if(m_id != 0) return false;
    initFile();
    m_id = GMySQL2().execQuery(GFORMAT(""
            " insert into _file "
            " ( _filename ) "
            " values ( '%s' ) "
            "", m_filename.c_str()
    )).getId();
    if(m_id == 0) return false;
    return true;
}
//===============================================
bool GFile3::updateFile() {
    if(m_id == 0) return false;
    m_fullname = GFORMAT("%s/%d_%s", m_rootPath.c_str(), m_id, m_filename.c_str());
    GMySQL2().execQuery(GFORMAT(""
            " update _file "
            " set _fullname = '%s' "
            " where _id = %d "
            "", m_id
    ));
    return true;
}
//===============================================
bool GFile3::saveContent() {
    if(m_id == 0) return false;
    GFile3 lFile(m_fullname);
    GString lDataBin(GBase64(m_content).decodeData());
    lFile.setContentBin(lDataBin);
    GLOG_ADD(eGLOG, "Le fichier a bien été enregistré.");
    return true;
}
//===============================================
bool GFile3::downloadFile() {

    return true;
}
//===============================================
