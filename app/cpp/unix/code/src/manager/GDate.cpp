//===============================================
#include "GDate.h"
//===============================================
const char* GDate::DATE_LOGTRACE = "%d/%m/%Y";
const char* GDate::DATE_FILENAME = "%Y_%m_%d";
const char* GDate::DATETIME_LOGTRACE = "%d/%m/%Y %H:%M:%S";
const char* GDate::DATETIME_FILENAME = "%Y_%m_%d_%H_%M_%S";
//===============================================
GDate::GDate() : GObject() {

}
//===============================================
GDate::~GDate() {

}
//===============================================
GString GDate::getDateTimeLogFormat() const {
    return "%d/%m/%Y %H:%M:%S";
}
//===============================================
GString GDate::getDateTimeFileFormat() const {
    return "%Y_%m_%d_%H_%M_%S";
}
//===============================================
GString GDate::getDateFileFormat() const {
    return "%Y_%m_%d";
}
//===============================================
GString GDate::getDate(const GString& _format) const {
    time_t lNow = time(0);
    struct tm  lTm;
    char lBuffer[80];
    lTm = *(localtime(&lNow));
    strftime(lBuffer, sizeof(lBuffer), _format.c_str(), &lTm);
    return lBuffer;
}
//===============================================
void GDate::setFormat(const GString& _format) {
    m_format = _format;
}
//===============================================
GString GDate::getDate() const {
    return m_date;
}
//===============================================
bool GDate::run() {
    if(m_format.isEmpty()) {
        m_logs.addError("Erreur le format de la date est obligatoire");
        return false;
    }
    time_t lNow = time(0);
    struct tm  lTm;
    char lBuffer[80];
    lTm = *(localtime(&lNow));
    strftime(lBuffer, sizeof(lBuffer), m_format.c_str(), &lTm);
    m_date = lBuffer;
    return !m_logs.hasErrors();
}
//===============================================
