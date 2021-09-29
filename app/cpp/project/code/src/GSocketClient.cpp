//===============================================
#include "GSocketClient.h"
#include "GManager.h"
//===============================================
GSocketClient::GSocketClient(QObject* parent) :
GSocketUi(parent) {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int argc, char** argv) {
	qDebug() << "[client] aucun process n'a ete selectionne.";
}
//===============================================
