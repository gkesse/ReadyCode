//===============================================
#include "GPocoPostXml.h"
#include "GFile.h"
#include "GPath.h"
#include "GManager.h"
//===============================================
GPocoPostXml::GPocoPostXml()
: GPoco() {

}
//===============================================
GPocoPostXml::~GPocoPostXml() {

}
//===============================================
GString GPocoPostXml::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "verb", m_verb);
    lDom.addData(_code, "method", m_method);
    lDom.addData(_code, "module", m_module);
    return lDom.toString();
}
//===============================================
void GPocoPostXml::deserialize(const GString& _data, const GString& _code) {
    m_verb = _data.extract(1, "/");
    m_method = _data.extract(2, "/");
    m_module = _data.extract(3, "/");
}
//===============================================
bool GPocoPostXml::run(const GString& _url) {
    GPocoPostXml lPoco;
    lPoco.deserialize(_url);
    if(lPoco.m_verb == "") {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le verbe est obligatoire.");
    }
    else if(lPoco.m_verb == "favicon.ico") {
        m_contentType = "image/png";
        GString lFavicon = GPATH("img", "readydev.png");
        m_response = GFile(lFavicon).getContentBin();
    }
    else {
        if(lPoco.m_verb == m_verb) {
            onPost();
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le verbe est inconnu.");
        }
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPocoPostXml::onPost() {
    GXml lXml;
    if(lXml.loadXml(m_request)) {
        GManager lManager;
        lManager.deserialize(m_request);
        if(lManager.isValid()) {
            m_logs.addLog("La requête a bien été exécutée.");
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le format de la requête est incorrect.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le format de la requête est invalide.");
    }
    return !m_logs.hasErrors();
}
//===============================================
