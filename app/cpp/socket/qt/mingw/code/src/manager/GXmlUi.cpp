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

    GXml lXml, lDoc;
    std::string lData;
    lXml.blank();
    lXml.load(lApp->xml_file);
    lXml.toString(lData, "UTF-8");
    printf("%s\n", lData.c_str());
    lDoc.parse(lData);
    lDoc.print();
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
