//===============================================
#include "GXmlRpcM.h"
//===============================================
GXmlRpcM::GXmlRpcM() {
    m_onExecute = 0;
}
//===============================================
GXmlRpcM::~GXmlRpcM() {

}
//===============================================
void GXmlRpcM::signature(const std::string _signature) {
    this->_signature = _signature;
}
//===============================================
void GXmlRpcM::help(const std::string _help) {
    this->_help = _help;
}
//===============================================
void GXmlRpcM::onExecute(onExecuteCB _onExecute) {
    m_onExecute = _onExecute;
}
//===============================================
void GXmlRpcM::execute(pList _params, pValue _value) {
    if(m_onExecute) {
        m_onExecute(_params, _value);
    }
}
//===============================================
