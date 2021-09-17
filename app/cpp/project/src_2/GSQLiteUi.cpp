//===============================================
#include "GSQLiteUi.h"
#include "GSQLiteDbUpdate.h"
#include "GSQLiteFieldsShow.h"
#include "GSQLiteTablesShow.h"
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
    if(key == "tablesshow") {return new GSQLiteTablesShow;}
    if(key == "fieldsshow") {return new GSQLiteFieldsShow;}
    return new GSQLiteUi;
}
//===============================================
void GSQLiteUi::run(int argc, char** argv) {
    qDebug() << "[sqlite] aucun process n'a ete selectionne.";
}
//===============================================
