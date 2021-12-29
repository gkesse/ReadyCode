//===============================================
#include "GFileUi.h"
#include "GResource.h"
//===============================================
GFileUi::GFileUi() {

}
//===============================================
GFileUi::~GFileUi() {

}
//===============================================
GFileUi* GFileUi::Create(const QString& _key) {
    if(_key == "default") return new GFileUi;
    return new GFileUi;
}
//===============================================
void GFileUi::run(int argc, char** argv) {
    qDebug() << GIMG("copy.png");
}
//===============================================
