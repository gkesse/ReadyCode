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

    GXml lXml, lProduct, lNew;

    lXml.parse(lApp->xml_file_01);
    lXml.root();
    lProduct.xpath(lXml, "/catalog/product[position()=1]");
    create(lNew, "REF123456", "Capteur ReadyDev", "10.00");
    lProduct.append(lNew);
    lXml.print();
    lXml.free();
}
//===============================================
void GXmlUi::create(GXml& _xml, const std::string& _reference, const std::string& _name, const std::string& _price) {
	_xml.node("product");
	_xml.attribute("reference", _reference);
    _xml.child("name", _name);
    _xml.child("price", _price);
}
//===============================================
