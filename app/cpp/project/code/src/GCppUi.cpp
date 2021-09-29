//===============================================
#include "GCppUi.h"
#include "GManager.h"
//===============================================
GCppUi::GCppUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GCppUi::~GCppUi() {

}
//===============================================
GCppUi* GCppUi::Create(const QString& key, QObject* parent) {
	if(key == "default") {return new GCppUi(parent);}
	return new GCppUi(parent);
}
//===============================================
void GCppUi::run(int argc, char** argv) {
	qDebug() << "[cpp] aucun process n'a ete selectionne.";
	sGApp* lApp = GManager::Instance()->getData()->app;
	xmlDocPtr doc = xmlParseFile(lApp->xml_file_path.c_str());

	if (doc == NULL ) {
		fprintf(stderr, "Le document n'a pas été analysé avec succès.\n");
		return;
	}

	xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);

	xmlFreeDoc(doc);
	xmlCleanupParser();
}
//===============================================
