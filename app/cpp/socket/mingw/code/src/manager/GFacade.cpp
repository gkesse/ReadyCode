//===============================================
#include "GFacade.h"
#include "GXml.h"
//===============================================
GFacade::GFacade() {

}
//===============================================
GFacade::~GFacade() {

}
//===============================================
void GFacade::getModule(const std::string& _dataIn, std::string& _module) {
    GXml lXml;
    lXml.parseData(_dataIn).getRoot();
    lXml.firstChild(lXml).getNodeValue(_module);
}
//===============================================
void GFacade::getMethod(const std::string& _dataIn, std::string& _method) {
    GXml lXml;
    lXml.parseData(_dataIn).getRoot();
    lXml.firstChild(lXml).nextSibling(lXml).getNodeValue(_method);
}
//===============================================
void GFacade::getData(const std::string& _dataIn, int _index, std::string& _data) {
    GXml lXml;
    lXml.parseData(_dataIn).getRoot();
    lXml.firstChild(lXml).nextSibling(lXml).nextSibling(lXml).firstChild(lXml);
    for(int i = 0; i < _index; i++) {
    	lXml.nextSibling(lXml);
    }
    lXml.getNodeValue(_data);
}
//===============================================
void GFacade::getPoint(sGPoint& _point, const std::string& _x, const std::string& _y, const std::string& _z) {
    _point.x = std::stof(_x);
    _point.y = std::stof(_y);
    _point.z = std::stof(_z);
}
//===============================================
