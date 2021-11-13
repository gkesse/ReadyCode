//===============================================
#include "GXmlUi.h"
#include "GXml.h"
#include "GManager.h"
#include "GStruct.h"
//===============================================
GXmlUi::GXmlUi() {

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
void GXmlUi::run(int _argc, char** _argv) {
    sGApp* lApp = GManager::Instance()->data()->app;

    GXml lDom, lChild, lNew;
    QString lData;

    lDom.load(lApp->xml_file_01);
    lDom.root(lDom);
    lDom.firstChild(lChild);
    lChild.firstChild(lChild);
    create(lDom, lNew, "NEW_NAME");
    lChild.replaceChild(lChild, lNew);
    lDom.toText(lData);
    qDebug() << lData;
}
//===============================================
void GXmlUi::create(GXml& _dom, GXml& _child, const QString& _name) {
    GXml lText;
    _dom.element(_child, "name");
    _dom.text(lText, _name);
    _child.appendChild(lText);

}
//===============================================
void GXmlUi::create(GXml& _dom, GXml& _child, const QString& _reference, const QString& _name, const QString& _price) {
    GXml lName, lNameText, lPrice, lPriceText;
    _dom.element(_child, "product");
    _dom.element(lName, "name");
    _dom.element(lPrice, "price");
    _dom.element(lNameText, _name);
    _dom.element(lPriceText, _price);
    lName.appendChild(lNameText);
    lPrice.appendChild(lPriceText);
    _child.attributes("reference", _reference);
    _child.appendChild(lName);
    _child.appendChild(lPrice);

}
//===============================================
