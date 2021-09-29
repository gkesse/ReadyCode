//===============================================
#include "GSocketUi.h"
#include "GSocketServer.h"
#include "GSocketClient.h"
#include "GManager.h"
//===============================================
GSocketUi::GSocketUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GSocketUi::~GSocketUi() {

}
//===============================================
GSocketUi* GSocketUi::Create(const QString& key, QObject* parent) {
	if(key == "default") {return new GSocketUi(parent);}
	if(key == "server") {return new GSocketServer(parent);}
	if(key == "client") {return new GSocketClient(parent);}
	return new GSocketUi(parent);
}
//===============================================
void GSocketUi::run(int argc, char** argv) {
	qDebug() << "[socket] aucun process n'a ete selectionne.";
}
//===============================================
