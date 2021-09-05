//===============================================
#include "GBoostUi.h"
#include "GServerAccept.h"
//===============================================
GBoostUi::GBoostUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GBoostUi::~GBoostUi() {

}
//===============================================
GBoostUi* GBoostUi::Create(const QString& key) {
    if(key == "default") {return new GBoostUi;}
    // server
    if(key == "server/accept") {return new GServerAccept;}
    // default
    return new GBoostUi;
}
//===============================================
void GBoostUi::run(int argc, char** argv) {
    qDebug() << "[boost] aucun process n'a ete selectionne.";
}
//===============================================
