//===============================================
#include "GHostname.h"
#include "GLog.h"
#include "GSocket.h"
//===============================================
GHostname::GHostname() : GObject() {

}
//===============================================
GHostname::~GHostname() {

}
//===============================================
void GHostname::onModule(std::string _req, GSocket* _client) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
