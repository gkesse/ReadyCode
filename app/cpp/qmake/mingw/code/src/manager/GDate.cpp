//===============================================
#include "GDate.h"
#include "GLog.h"
//===============================================
GDate::GDate(QObject* _parent) : GObject(_parent) {

}
//===============================================
GDate::~GDate() {

}
//===============================================
QString GDate::getDateTimeLogFormat() const {
    return "%d/%m/%Y %H:%M:%S";
}
//===============================================
QString GDate::getDateTimeFileFormat() const {
    return "%Y_%m_%d_%H_%M_%S";
}
//===============================================
QString GDate::getDateFileFormat() const {
    return "%Y_%m_%d";
}
//===============================================
QString GDate::getDate(const QString& _format) const {
    time_t lNow = time(0);
    struct tm  lTm;
    char lBuffer[80];
    lTm = *(localtime(&lNow));
    strftime(lBuffer, sizeof(lBuffer), _format.toStdString().c_str(), &lTm);
    return lBuffer;
}
//===============================================
