//===============================================
#include "GSQLiteUi.h"
#include "GSQLite.h"
#include "GResource.h"
#include "GConsole.h"
#include "GStruct.h"
//===============================================
GSQLiteUi::GSQLiteUi() {

}
//===============================================
GSQLiteUi::~GSQLiteUi() {

}
//===============================================
GSQLiteUi* GSQLiteUi::Create(const QString& _key) {
    if(_key == "default") return new GSQLiteUi;
    return new GSQLiteUi;
}
//===============================================
void GSQLiteUi::run(int argc, char** argv) {
    std::vector<std::string> lNames;
    std::vector<std::vector<std::string>> lData = GSQLITE->readMap(""
            " select * from user_data "
            "", &lNames);
    GCONSOLE->showData(lNames);
    GCONSOLE->showData(lData);
}
//===============================================
