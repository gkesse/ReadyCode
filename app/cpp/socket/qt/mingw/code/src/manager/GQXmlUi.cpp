//===============================================
#include "GQXmlUi.h"
#include "GQXml.h"
#include "GManager.h"
#include "GStruct.h"
//===============================================
GQXmlUi::GQXmlUi() {

}
//===============================================
GQXmlUi::~GQXmlUi() {

}
//===============================================
GQXmlUi* GQXmlUi::Create(const QString& _key) {
    if(_key == "default") {return new GQXmlUi;}
    return new GQXmlUi;
}
//===============================================
void GQXmlUi::run(int _argc, char** _argv) {
	sGApp* lApp = GManager::Instance()->data()->app;

	sGQXml lParams;
	GQXml lDom, lRoot, lChild;
	QString lData;

	lDom.fileRead(lApp->xml_file_01);
	lDom.content();
	lDom.root(lRoot);
	lRoot.tagName(lData);
	qDebug() << "Data.....: " << lData;
	lRoot.firstChild(lChild);
	while(!lChild.isNull()) {
		lChild.tagName(lData);
		qDebug() << "Child....: " << lData;
		lChild.nextSibling(lChild);
	}

	lDom.close();
}
//===============================================
