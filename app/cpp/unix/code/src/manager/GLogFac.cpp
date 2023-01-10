//===============================================
#include "GLogFac.h"
#include "GShell.h"
#include "GCode.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile.h"
#include "GPath.h"
#include "GApp.h"
//===============================================
GLogFac::GLogFac()
: GManager() {

}
//===============================================
GLogFac::~GLogFac() {

}
//===============================================
GString GLogFac::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    //lDom.addData(_code, "id", m_id);
    return lDom.toString();
}
//===============================================
void GLogFac::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    //m_id = lDom.getData(_code, "id").toInt();
}
//===============================================
bool GLogFac::onModule(const GString& _data) {
    deserialize(_data);
    if(m_methodName == "") {
        m_logs.addError("Erreur la méthode est obligatoire.");
    }
    else if(m_methodName == "cat_log_file") {
        onCatLogFile();
    }
    else if(m_methodName == "tail_log_file") {
        onTailLogFile();
    }
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GLogFac::onCatLogFile() {
    catLogFile();
    return !m_logs.hasErrors();
}
//===============================================
bool GLogFac::onTailLogFile() {
    tailLogFile();
    return !m_logs.hasErrors();
}
//===============================================
bool GLogFac::catLogFile() {
    GFile lFile(m_logFilename);
    if(lFile.existFile()) {
        printf("%s\n", lFile.getContent().c_str());
    }
    else {
        m_logs.addError("Le fichier des logs n'est pas initialisé.");
        GLOGT(eGERR, "Le fichier des logs n'est pas initialisé.\n%s", m_logFilename.c_str());
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GLogFac::tailLogFile() {
    GFile lFile(m_logFilename);
    if(lFile.existFile()) {
        GShell().tailFile(m_logFilename);
    }
    else {
        m_logs.addError("Le fichier des logs n'est pas initialisé.");
        GLOGT(eGERR, "Le fichier des logs n'est pas initialisé.\n%s", m_logFilename.c_str());
    }
    return !m_logs.hasErrors();
}
//===============================================
