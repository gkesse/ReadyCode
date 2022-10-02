//===============================================
#include "GDate2.h"
//===============================================
GDate2::GDate2()
: GObject() {

}
//===============================================
GDate2::~GDate2() {

}
//===============================================
GString GDate2::getDateTimeLogFormat() const {
    return "%d/%m/%Y %H:%M:%S";
}
//===============================================
GString GDate2::getDateTimeFileFormat() const {
    return "%Y_%m_%d_%H_%M_%S";
}
//===============================================
GString GDate2::getDateFileFormat() const {
    return "%Y_%m_%d";
}
//===============================================
GString GDate2::getDate(const GString& _format) const {
    time_t lNow = time(0);
    struct tm  lTm;
    char lBuffer[80];
    lTm = *(localtime(&lNow));
    strftime(lBuffer, sizeof(lBuffer), _format.c_str(), &lTm);
    return lBuffer;
}
//===============================================
