//===============================================
#include "GMd5.h"
#include "GCode.h"
#include "GSocket.h"
#include "GLog.h"
//===============================================
GMd5::GMd5() : GModule() {
    m_dataIn = "";
    m_dataOut = "";
}
//===============================================
GMd5::~GMd5() {

}
//===============================================
GString GMd5::serialize(const GString& _code) const {
    GCode lReq;
    lReq.createDoc();
    lReq.addData(_code, "data_in", m_dataIn);
    lReq.addData(_code, "data_out", m_dataOut);
    return lReq.toStringData();
}
//===============================================
void GMd5::deserialize(const GString& _data, const GString& _code) {
    GModule::deserialize(_data);
    GCode lReq;
    lReq.loadXml(_data);
    m_dataIn = lReq.getItem(_code, "data_in");
    m_dataOut = lReq.getItem(_code, "data_out");
}
//===============================================
bool GMd5::onModule(GSocket* _client) {
    deserialize(_client->toReq());
    //===============================================
    if(m_method == "") {
        return false;
    }
    //===============================================
    // method
    //===============================================
    else if(m_method == "encode_data") {
        onEncodeData(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onMethodUnknown(_client);
    }
    //===============================================
    return true;
}
//===============================================
bool GMd5::onEncodeData(GSocket* _client) {
    if(m_dataIn == "") {GERROR_ADD(eGERR, "La donnée est vide."); return false;}
    m_dataOut = encodeData(m_dataIn);
    GString lData = serialize();
    _client->addResponse(lData);
    return true;
}
//===============================================
GString GMd5::encodeData(const GString& _data) const {
    if(_data == "") return "";
    MD5 lMd5;
    GString lData = lMd5(_data);
    return lData;
}
//===============================================
