//===============================================
#include "GMd5_2.h"
//===============================================
GMd5_2::GMd5_2()
: GModule2() {

}
//===============================================
GMd5_2::~GMd5_2() {

}
//===============================================
GString2 GMd5_2::encodeData(const GString2& _data) const {
    if(_data == "") return "";
    MD5 lMd5;
    GString2 lData = lMd5(_data.data());
    return lData;
}
//===============================================