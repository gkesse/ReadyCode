//===============================================
#include "GLogUi.h"
#include "GShell.h"
#include "GCode.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile.h"
#include "GPath.h"
#include "GApp.h"
//===============================================
GLogUi* GLogUi::m_instance = 0;
//===============================================
GLogUi::GLogUi() {
    m_isFileLog = false;
    m_isDebug = false;
    m_isProdFile = false;
    m_isProdLog = false;
    m_isTestFile = false;
    m_isTestLog = false;
    m_isTestEnv = false;
    m_file = 0;
}
//===============================================
GLogUi::~GLogUi() {

}
//===============================================
GLogUi* GLogUi::Instance() {
    if(m_instance == 0) {
        m_instance = new GLogUi;
        m_instance->initLog();
    }
    return m_instance;
}
//===============================================
void GLogUi::initLog() {
    GEnv lEnv;
    m_file = 0;

    m_isTestEnv     = lEnv.isTestEnv();
    m_isTestLog     = (GAPP->getData("log", "test_on") == "1");
    m_isProdLog     = (GAPP->getData("log", "prod_on") == "1");
    m_isTestFile    = (GAPP->getData("log", "test_file_on") == "1");
    m_isProdFile    = (GAPP->getData("log", "prod_file_on") == "1");
    m_isDebug       = (m_isTestEnv ? m_isTestLog : m_isProdLog);
    m_isFileLog     = (m_isTestEnv ? m_isTestFile : m_isProdFile);

    m_tmpPath       = lEnv.getTmpDir();
    m_currentDate   = GDate().getDateFileFormat();
    m_logTestFile   = GFORMAT("%s/log_test_%s.txt", m_tmpPath.c_str(), m_currentDate.c_str());
    m_logProdFile   = GFORMAT("%s/log_prod_%s.txt", m_tmpPath.c_str(), m_currentDate.c_str());
    m_logFilename   = (m_isTestEnv ? m_logTestFile : m_logProdFile);
}
//===============================================
FILE* GLogUi::getOutput() {
    FILE* lFile = stdout;
    if(m_isFileLog) lFile = getOutputFile();
    return lFile;
}
//===============================================
FILE* GLogUi::getOutputFile() {
    FILE* lFile = fopen(m_logFilename.c_str(), "a+");
    m_file = lFile;
    return lFile;
}
//===============================================
void GLogUi::closeLogFile() {
    if(!m_file) return;
    fclose(m_file);
    m_file = 0;
}
//===============================================
void GLogUi::catLogFile() {
    GFile lFileObj(m_logFilename);
    GString lData = GFORMAT("Le fichier log n'existe pas :\n(%s)", m_logFilename.c_str());
    if(lFileObj.existFile()) {
        lData = lFileObj.getContent();
    }
    printf("%s\n", lData.c_str());
}
//===============================================
void GLogUi::tailLogFile(bool _isTestEnv) {
    GFile lFileObj(m_logFilename);
    GString lData = GFORMAT("Le fichier log n'existe pas :\n(%1)", m_logFilename.c_str());
    if(lFileObj.existFile()) {
        GShell().tailFile(m_logFilename);
    }
    else {
        printf("%s\n", lData.c_str());
    }
}
//===============================================
void GLogUi::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(_level == 0) return;
    if(!m_isDebug) return;
    fprintf(getOutput(), "%s\n", _data.c_str());
    closeLogFile();
}
//===============================================
void GLogUi::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(_level == 0) return;
    if(!m_isDebug) return;
    GString lDate = GDate().getDate(GDate().getDateTimeLogFormat());
    fprintf(getOutput(), "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.c_str(), _file, _line, _func, _data.c_str());
    closeLogFile();
}
//===============================================
