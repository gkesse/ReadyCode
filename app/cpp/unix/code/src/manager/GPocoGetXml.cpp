//===============================================
#include "GPocoGetXml.h"
#include "GFile.h"
#include "GPath.h"
//===============================================
GPocoGetXml::GPocoGetXml()
: GPoco() {

}
//===============================================
GPocoGetXml::~GPocoGetXml() {

}
//===============================================
GString GPocoGetXml::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "verb", m_verb);
    lDom.addData(_code, "method", m_method);
    lDom.addData(_code, "module", m_module);
    return lDom.toString();
}
//===============================================
void GPocoGetXml::deserialize(const GString& _data, const GString& _code) {
    m_verb = _data.extract(1, "/");
    m_method = _data.extract(2, "/");
    m_module = _data.extract(3, "/");
}
//===============================================
bool GPocoGetXml::run(const GString& _url) {
    deserialize(_url);
    if(m_verb == "") {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur le verbe est obligatoire.");
    }
    else if(m_verb == "favicon.ico") {
        m_contentType = "image/png";
        GString lFavicon = GPATH("img", "readydev.png");
        m_response = GFile(lFavicon).getContentBin();
    }
    else {
        if(m_verb == m_verb.c_str()) {
            m_logs.addLog("La requête a bien été exécutée.");
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur le verbe est inconnu.");
        }

        m_responseXml.loadData(m_logs.serialize());
        m_response = m_responseXml.toString();
    }
    return !m_logs.hasErrors();
}
//===============================================
