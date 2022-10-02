//===============================================
#include "GDate.h"
//===============================================
GDate::GDate()
: GObject() {

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
