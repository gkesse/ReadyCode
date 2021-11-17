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
    lXml.removeBlank();
    lXml.createDoc();
    lXml.createRoot("catalog");
    lXml.appendChild(lProduct, "product");
    lProduct.attribute("reference", "REF123");
    lProduct.appendChild("name", "ZigBee ReadyDev");
    lProduct.appendChild("price", "2.50");
    lXml.save(lApp->xml_file, "UTF-8");
    lXml.freeDoc();
}
//===============================================
void GXmlUi::append(GXml& _xml, const std::string& _reference, const std::string& _name, const std::string& _price) {
    _xml.node("product");
    _xml.attribute("reference", _reference);
    _xml.child("name", _name);
    _xml.child("price", _price);
}
//===============================================
