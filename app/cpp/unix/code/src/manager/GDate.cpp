//===============================================
#include "GDate.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GDate::GDate() : GObject() {

}
//===============================================
GDate::~GDate() {

}
//===============================================
std::string GDate::getDateTimeFormat() const {
    return "%d/%m/%Y %H:%M:%S";
}
//===============================================
std::string GDate::getLogFormat() const {
    return "%Y_%m_%d_%H_%M_%S";
}
//===============================================
std::string GDate::getDate(const std::string& _format) {
    time_t lNow = time(0);
    struct tm  lTm;
    char lBuffer[80];
    lTm = *(localtime(&lNow));
    strftime(lBuffer, sizeof(lBuffer), _format.c_str(), &lTm);
    return lBuffer;
}
//===============================================
