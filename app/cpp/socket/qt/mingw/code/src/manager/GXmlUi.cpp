//===============================================
#include "GXmlUi.h"
#include "GXml.h"
#include "GManager.h"
//===============================================
GXmlUi::GXmlUi(QObject* _parent) :
GObject(_parent) {

}
//===============================================
GXmlUi::~GXmlUi() {

}
//===============================================
GXmlUi* GXmlUi::Create(const QString& _key) {
    if(_key == "default") {return new GXmlUi;}
    return new GXmlUi;
}
//===============================================
void GXmlUi::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->data()->app;

    GXml lXml, lProduct;
    std::string lData;
    lXml.blank();
    lXml.doc();
    lXml.root("catalog");
    lXml.child(lProduct, "product");
    lProduct.attribute("reference", "REF123");
    lProduct.childs("name", "ZigBee ReadyDev");
    lProduct.childs("price", "2.50");
    lXml.save(lApp->xml_file, "UTF-8");
    lXml.free();
}
//===============================================
void GXmlUi::append(GXml& _xml, const std::string& _reference, const std::string& _name, const std::string& _price) {
    _xml.node("product");
    _xml.attribute("reference", _reference);
    _xml.child("name", _name);
    _xml.child("price", _price);
}
//===============================================
