//===============================================
#include "GMap.h"
#include "GCode.h"
//===============================================
GMap::GMap()
: GCode() {
    createDoc();
}
//===============================================
GMap::GMap(const GString& _data)
: GCode() {
    loadXml(_data);
}
//===============================================
GMap::~GMap() {

}
//===============================================
void GMap::addObject(const GString& _key, const GString& _obj, const GString& _code) {
    addData(_code, _key, _obj.toBase64());
}
//===============================================
GString GMap::getObject(const GString& _key, const GString& _code) {
    return getData(_code, _key).fromBase64();
}
//===============================================
