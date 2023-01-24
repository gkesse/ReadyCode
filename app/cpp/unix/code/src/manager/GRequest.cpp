//===============================================
#include "GRequest.h"
#include "GHttp.h"
//===============================================
GRequest::GRequest()
: GObject() {

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
        lLineNum++;
        if(lLine.isEmpty()) {
            break;
        }
        lLine.print();

        if(++lLinePos == NBR_LINE_MAX) {
            m_logs.addError("Le nombre de lignes maximal a été atteint.");
            break;
        }
    }

    GHttp lHttp;
    lHttp.setModule("response");
    lHttp.setContentText("[POST] Bonjour tout le monde !");
    lHttp.run();
    m_logs.addLogs(lHttp.getLogs());
    m_response = lHttp.getResponseText();
    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::runApp() {
    return !m_logs.hasErrors();
}
//===============================================
