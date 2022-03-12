//===============================================
#include "GMaster.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
//===============================================
GMaster::GMaster() : GObject() {

}
//===============================================
GMaster::~GMaster() {

}
//===============================================
void GMaster::onModuleMaster(std::string _req, GSocket* _client) {
    GXml lReq;
    lReq.loadXmlData(_req);
    lReq.createXPath();
    std::string lModule = lReq.getNodeValue("/rdv/module");
    std::string lMethod = lReq.getNodeValue("/rdv/method");
    printf("=====>\n");
    printf("%s\n", lModule.c_str());
    printf("%s\n", lMethod.c_str());
}
//===============================================
