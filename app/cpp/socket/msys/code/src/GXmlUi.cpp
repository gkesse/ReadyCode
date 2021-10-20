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
    sGApp* lApp = GManager::Instance()->data()->app;

    GXml lXml;
    lXml.filename(lApp->xml_file);
    lXml.parse();
    lXml.root();

    GXml lProduct_1;
    lProduct_1.xpath(lXml, "/catalog/product[position()=1]");
    lProduct_1.print(lXml);

    lXml.free();
}
//===============================================
