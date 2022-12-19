//===============================================
#include "GSocketHttpApp.h"
#include "GManager.h"
#include "GEnv.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
GSocketHttpApp::GSocketHttpApp()
: GSocket() {
    m_diffSize = 0;
    m_headerSize = 0;
    m_dataSize = 0;
    m_port = 0;
    m_contentLength = 0;
    m_status = 200;
    m_reason = "OK";
    m_version = "HTTP/1.1";
    m_connection = "Close";
    m_contentType = "text/html";
}
//===============================================
GSocketHttpApp::~GSocketHttpApp() {

}
//===============================================
bool GSocketHttpApp::runThreadCB() {
    runRequest();
    sendResponse();
    close(m_socket);
    delete this;
    return true;
}
//===============================================
bool GSocketHttpApp::runRequest() {
    if(!readMethod()) return false;
    if(!isValidRequest()) return false;
    if(!readHeader()) return false;
    //if(!readData(m_diffSize)) return false;
    if(!readRequest()) return false;
    analyzeRequest();
    integrateErrors();
    createResponse();
    createData();
    return true;
}
//===============================================
bool GSocketHttpApp::readMethod() {
    char lBuffer[METHOD_SIZE + 1];
    int lBytes = readData(lBuffer, METHOD_SIZE);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    m_dataIn += lBuffer;
    return true;
}
//===============================================
bool GSocketHttpApp::isValidRequest() {
    if(!m_dataIn.startBy(GSocket::METHOD_HTTP_GET)) return true;
    if(!m_dataIn.startBy(GSocket::METHOD_HTTP_POST)) return true;
    return false;
}
//===============================================
bool GSocketHttpApp::readHeader() {
    int lIndex = 0;
    GString lLine = "";

    for(int i = 0; i < m_dataIn.size(); i++) {
        char lChar = m_dataIn[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            m_method = lLine.extract(0, " \r\n").trim();
            m_url = lLine.extract(1, " \r\n").trim();
            m_version = lLine.extract(2, " \r\n").trim();
            lLine = "";
            break;
        }
    }
    for(int i = 0; i < m_dataIn.size(); i++) {
        char lChar = m_dataIn[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            if(lLine.startBy("Host")) {
                m_hostname = lLine.extract(1, ":\r\n").trim();
                m_port = lLine.extract(2, ":\r\n").trim().toInt();
            }
            else if(lLine.startBy("Content-Type")) {
                m_contentType = lLine.extract(1, ":\r\n").trim();
            }
            else if(lLine.startBy("Content-Length")) {
                m_contentLength = lLine.extract(1, ":\r\n").trim().toInt();
            }
            lLine = "";
        }
    }
    return true;
}
//===============================================
bool GSocketHttpApp::readRequest() {
    return true;
}
//===============================================
bool GSocketHttpApp::analyzeRequest() {
    return true;
}
//===============================================
bool GSocketHttpApp::integrateErrors() {
    return true;
}
//===============================================
bool GSocketHttpApp::createResponse() {
    GSocketHttpApp lResponse;
    lResponse.m_content += "<h1>Bonjour tout le monde</h1>";
    lResponse.createData();
    m_dataOut = lResponse.m_dataOut;
    return true;
}
//===============================================
bool GSocketHttpApp::createData() {
    if(m_version == "") return false;
    if(m_status == 0) return false;
    if(m_reason == "") return false;
    if(m_contentType == "") return false;

    m_dataOut += GFORMAT("%s %d %s\r\n", m_version.c_str(), m_status, m_reason.c_str());
    m_dataOut += GFORMAT("Content-Type: %s\r\n", m_contentType.c_str());

    if(m_content.size() > 0) {
        m_dataOut += GFORMAT("Content-Length: %d\r\n", m_content.size());
    }

    if(m_connection != "") {
        m_dataOut += GFORMAT("Connection: %s\r\n", m_connection.c_str());
    }

    m_dataOut += GFORMAT("\r\n");
    m_dataOut += GFORMAT("%s", m_content.c_str());
    return true;
}
//===============================================
bool GSocketHttpApp::isLine(char _char, int& _index) const {
    if(_index == 0) {
        if(_char == '\r')_index++; else _index = 0;
    }
    else if(_index == 1) {
        if(_char == '\n') _index++; else _index = 0;
    }

    if(_index == 2) {_index = 0; return true;}
    return false;
}
//===============================================
bool GSocketHttpApp::isHeader(char _char, int& _index) const {
    if(_index == 0) {
        if(_char == '\r')_index++; else _index = 0;
    }
    else if(_index == 1) {
        if(_char == '\n') _index++; else _index = 0;
    }
    else if(_index == 2) {
        if(_char == '\r') _index++; else _index = 0;
    }
    else if(_index == 3) {
        if(_char == '\n') _index++; else _index = 0;
    }

    if(_index == 4) return true;
    return false;
}
//===============================================
