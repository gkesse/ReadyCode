//===============================================
#include "GList.h"
//===============================================
GList::GList() {

}
//===============================================
GList::~GList() {

}
//===============================================
GString GList::toSqlArrayString() const {
    GString lData;
    for(int i = 0; i < (int)size(); i++) {
        GString lItem = at(i);
        if(i != 0) lData += ",";
        lData += GFORMAT("'%s'", lItem.c_str());
    }
    return lData;
}
//===============================================
GString GList::toSqlArrayInt() const {
    GString lData;
    for(int i = 0; i < (int)size(); i++) {
        GString lItem = at(i);
        if(i != 0) lData += ",";
        lData += GFORMAT("%s", lItem.c_str());
    }
    return lData;
}
//===============================================
