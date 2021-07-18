//===============================================
#include "GSQLiteUi.h"
#include "GSQLiteDbUpdate.h"
//===============================================
GSQLiteUi::GSQLiteUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GSQLiteUi::~GSQLiteUi() {

}
//===============================================
GSQLiteUi* GSQLiteUi::Create(const QString& key) {
    if(key == "default") {return new GSQLiteUi;}
    if(key == "dbupdate") {return new GSQLiteDbUpdate;}
    return new GSQLiteUi;
}
//===============================================
void GSQLiteUi::run(int argc, char** argv) {
    qDebug() << "[sqlite] aucun process n'a ete selectionne.";
}
//===============================================
