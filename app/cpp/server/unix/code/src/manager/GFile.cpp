//===============================================
#include "GFile.h"
#include "GMySQL.h"
//===============================================
GFile::GFile()
: GManager() {
    m_id = 0;
    m_size = 0;
}
//===============================================
GFile::~GFile() {

}
//===============================================
GString GFile::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "mime_type", m_mimeType);
    lDom.addData(_code, "size", m_size);
    lDom.addData(_code, "size", m_createDate.toString());
    lDom.addData(_code, "size", m_updateDate.toString());
    lDom.addData(_code, "data", m_data);
    return lDom.toString();
}
//===============================================
void GFile::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    m_mimeType = lDom.getData(_code, "mimeType");
    m_size = lDom.getData(_code, "size").toInt();
    m_createDate = lDom.getData(_code, "create_date").toDateTime();
    m_updateDate = lDom.getData(_code, "update_date").toDateTime();
    m_data = lDom.getData(_code, "data");
}
//===============================================
void GFile::run(const GString& _data) {
    deserialize(_data);
    if(m_method == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_method == "save_file") {
        onSaveFile(_data);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GFile::onSaveFile(const GString& _data) {
    if(m_name == "") {
        m_logs.addError("Le nom du fichier est obligatoire.");
        return;
    }
    if(m_data == "") {
        m_logs.addError("Le contenu du fichier est obligatoire.");
        return;
    }
    GString lPath = spath(sformat("/%s", m_name.c_str()));
    std::ofstream lFile(lPath.c_str(), std::ios::out | std::ios::binary);
    GString lData = m_data.fromBase64();
    lFile.write(lData.c_str(), lData.size());
}
//===============================================
