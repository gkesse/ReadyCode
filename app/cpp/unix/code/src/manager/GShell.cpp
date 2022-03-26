//===============================================
#include "GShell.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GShell::GShell() : GObject() {

}
//===============================================
GShell::~GShell() {

}
//===============================================
void GShell::runSystem(const std::string& _command) {
    std::string lCommand = sformat("%s > %s", _command.c_str());
    system(lCommand.c_str());
}
//===============================================
