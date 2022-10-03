//===============================================
#include "GDate.h"
//===============================================
GDate::GDate()
: GObject() {
    initDate();
}
//===============================================
GDate::~GDate() {

}
//===============================================
void GDate::initDate() {
    m_dateTimeLogFormat = "%d/%m/%Y %H:%M:%S";
    m_dateTimeFileFormat = "%Y_%m_%d_%H_%M_%S";
    m_dateFileFormat = "%Y_%m_%d";
}
//===============================================
GString GDate::getDateTimeLogFormat() const {
    return getDate(m_dateTimeLogFormat);
}
//===============================================
GString GDate::getDateTimeFileFormat() const {
    return getDate(m_dateTimeFileFormat);
}
//===============================================
GString GDate::getDateFileFormat() const {
    return getDate(m_dateFileFormat);
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
