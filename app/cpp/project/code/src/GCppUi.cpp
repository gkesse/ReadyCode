//===============================================
#include "GCppUi.h"
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
}
//===============================================
