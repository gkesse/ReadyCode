//===============================================
#include "GXmlUi.h"
#include "GXml.h"
#include "GManager.h"
//===============================================
GXmlUi::GXmlUi() {

}
//===============================================
GXmlUi::~GXmlUi() {

}
//===============================================
GXmlUi* GXmlUi::Create(const std::string& key) {
    if(key == "default") {return new GXmlUi;}
    return new GXmlUi;
}
//===============================================
void GXmlUi::run(int argc, char** argv) {
    sGApp* lApp = GResource::Instance()->getData()->app;

    GXml lXml;
    lXml.filename(lApp->xml_file);
    lXml.removeBlank();
    lXml.parse();
    lXml.root();

    GXml lProduct;
    lProduct.xpath(lXml, "/catalog/product[position()=1]");

    GXml lNew;
    lNew.create("REF123456", "Capteur ReadyDev", "10.00");

    lProduct.append(lNew);

    lXml.print();

    lXml.freeDoc();
}
//===============================================
