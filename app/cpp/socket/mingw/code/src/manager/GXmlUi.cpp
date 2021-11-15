//===============================================
#include "GXmlUi.h"
#include "GXml.h"
#include "GDefine.h"
#include "GManager.h"
//===============================================
GXmlUi::GXmlUi() {

}
//===============================================
GXmlUi::~GXmlUi() {

}
//===============================================
GXmlUi* GXmlUi::Create(const std::string& _key) {
    if(_key == "default") {return new GXmlUi;}
    return new GXmlUi;
}
//===============================================
void GXmlUi::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->data()->app;
    GXml lXml;
    std::string lData;
    lXml.createDoc();
    lXml.addVersion("1.0");
    lXml.addEncoding("UTF-8");
    lXml.createRoot("catalog");
    append(lXml, "REF123", "ZigBee ReadyDev", "2.50");
    lXml.docToString(lData);
    printf("%s\n", lData.c_str());
}
//===============================================
void GXmlUi::append(GXml& _xml, const std::string& _reference, const std::string& _name, const std::string& _price) {
    GXml lProduct, lName, lPrice;
    _xml.appendChild(lProduct, "product");
    lProduct.appendAttribute("reference", _reference);
    lProduct.appendChild(lName, "name");
    lName.setNodeValue(_name);
    lProduct.appendChild(lPrice, "price");
    lPrice.setNodeValue(_price);
}
//===============================================
