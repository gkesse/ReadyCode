//===============================================
#include "GRequest.h"
#include "GManager.h"
#include "GHttp.h"
//===============================================
GRequest::GRequest()
: GObject() {
    m_status = GHttp::HTTP_OK;
    m_contentType = "application/xml";
}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::setRequest(const GString& _request) {
    m_request = _request;
}
//===============================================
GString GRequest::getResponse() const {
    return m_response;
}
//===============================================
bool GRequest::run() {
    if(m_request.isEmpty()) {
        m_logs.addError("La requête est obligatoire.");
        return false;
    }
    if(m_request.startBy("GET ")) {
        runGet();
    }
    else if(m_request.startBy("POST ")) {
        runPost();
    }
    else {
        runApp();
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::runGet() {
    GHttp lHttp;
    lHttp.setModule("response");
    lHttp.setContentText("[GET] Bonjour tout le monde !");
    lHttp.run();
    m_logs.addLogs(lHttp.getLogs());
    m_response = lHttp.getResponseText();
    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::runPost() {
    int lLineNum = 0;
    int lLinePos = 0;
    GString lLineSep = "\r\n";
    GString lLine;

    while(1) {
        lLine = m_request.extract(lLineNum++, lLineSep);
        lLineNum += 1;
        m_request.move(1);
        if(lLine.isEmpty()) {
            m_request.move(1);
            m_requestBody = m_request.end();
            break;
        }

        if(++lLinePos == NBR_LINE_MAX) {
            m_logs.addError("Le nombre de lignes maximal a été atteint.");
            break;
        }
    }
    runPostRequest();
    runHttp();
    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::runApp() {
    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::runPostRequest() {
    if(m_requestBody.isEmpty()) {
        m_logs.addError("Le corps de la requête est obligatoire.");
        return false;
    }
    GXml lXml;
    if(lXml.loadXml(m_requestBody)) {
        GManager lManager;
        lManager.deserialize(m_requestBody);
        if(lManager.isValid()) {
            runManager();
        }
        else {
            m_status = GHttp::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le format de la requête est incorrect.");
        }
    }
    else {
        m_status = GHttp::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le format de la requête est invalide.");
    }
    m_responseXml.loadData(m_logs.serialize());
    m_responseBody = m_responseXml.toString();
    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::runHttp() {
    GHttp lHttp;
    lHttp.setModule("response");
    lHttp.setStatus(m_status);
    lHttp.setContentType(m_contentType);
    lHttp.setContentText(m_responseBody);
    lHttp.run();
    m_logs.addLogs(lHttp.getLogs());
    m_response = lHttp.getResponseText();
    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::runManager() {
    GManager lManager;
    lManager.run(m_requestBody);
    m_logs.addLogs(lManager.getLogs());
    m_responseXml.loadData(lManager.toResponse());
    return !m_logs.hasErrors();
}
//===============================================

