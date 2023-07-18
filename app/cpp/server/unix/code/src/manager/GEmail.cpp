//===============================================
#include "GEmail.h"
#include "GCurl.h"
//===============================================
// GEmail
//===============================================
GEmail::GEmail()
: GManager() {
    m_addrReply.setAddr("readydevz@gmail.com", "ReadyDev");
}
//===============================================
GEmail::~GEmail() {

}
//===============================================
void GEmail::setSubject(const GString& _subject) {
    m_subject = _subject;
}
//===============================================
void GEmail::setBody(const GString& _body) {
    m_body = _body;
}
//===============================================
void GEmail::setNoReply() {
    m_addrReply.setAddr("no-reply@readydev.com", "No-Reply [ReadyDev]");
}
//===============================================
GEmail::GAddr& GEmail::getTo() {
    return m_addrTo;
}
//===============================================
GEmail::GAddr& GEmail::getReply() {
    return m_addrReply;
}
//===============================================
GEmail::GAddr& GEmail::getCC() {
    return m_addrCC;
}
//===============================================
GEmail::GAddr& GEmail::getBCC() {
    return m_addrBCC;
}
//===============================================
GEmail::GAttach& GEmail::getAttach() {
    return m_attachFile;
}
//===============================================
GString GEmail::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "subject", m_subject);
    lDom.addData(_code, "body", m_body.toBase64());
    lDom.addData(_code, "addr_to", m_addrTo.serialize().toBase64());
    lDom.addData(_code, "addr_reply", m_addrReply.serialize().toBase64());
    lDom.addData(_code, "addr_cc", m_addrCC.serialize().toBase64());
    lDom.addData(_code, "addr_bcc", m_addrBCC.serialize().toBase64());
    lDom.addData(_code, "attach_file", m_attachFile.serialize().toBase64());
    return lDom.toString();
}
//===============================================
void GEmail::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_subject = lDom.getData(_code, "subject");
    m_body = lDom.getData(_code, "body").fromBase64();
    m_addrTo.deserialize(lDom.getData(_code, "addr_to").fromBase64());
    m_addrReply.deserialize(lDom.getData(_code, "addr_reply").fromBase64());
    m_addrCC.deserialize(lDom.getData(_code, "addr_cc").fromBase64());
    m_addrBCC.deserialize(lDom.getData(_code, "addr_bcc").fromBase64());
    m_attachFile.deserialize(lDom.getData(_code, "attach_file").fromBase64());
}
//===============================================
void GEmail::sendEmail() {
    GCurl lCurl;
    GString lData = serialize();
    lData = lCurl.postHttpsFormFacade("email", "send_email", lData);
    m_logs.addLogs(lCurl.getLogs());
    deserialize(lData);
}
//===============================================
// GEmail::GAddr
//===============================================
GEmail::GAddr::GAddr()
: GObject() {

}
//===============================================
GEmail::GAddr::~GAddr() {
    clearMap();
}
//===============================================
GEmail::GAddr* GEmail::GAddr::clone() {
    return new GEmail::GAddr;
}
//===============================================
void GEmail::GAddr::setObj(const GEmail::GAddr& _obj) {
    m_email = _obj.m_email;
    m_name = _obj.m_name;
}
//===============================================
void GEmail::GAddr::setAddr(const GString& _email, const GString& _name) {
    m_email = _email;
    m_name = _name;
}
//===============================================
void GEmail::GAddr::addAddr(const GString& _email, const GString& _name) {
    GAddr* lObj = new GEmail::GAddr;
    lObj->m_email = _email;
    lObj->m_name = _name;
    m_map.push_back(lObj);
}
//===============================================
GString GEmail::GAddr::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "email", m_email);
    lDom.addData(_code, "name", m_name);
    lDom.addMap(_code, m_map);
    return lDom.toString();
}
//===============================================
void GEmail::GAddr::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_email = lDom.getData(_code, "email");
    m_name = lDom.getData(_code, "name");
    lDom.getMap(_code, m_map, this);
}
//===============================================
// GEmail::GAttach
//===============================================
GEmail::GAttach::GAttach()
: GObject() {

}
//===============================================
GEmail::GAttach::~GAttach() {
    clearMap();
}
//===============================================
GEmail::GAttach* GEmail::GAttach::clone() {
    return new GEmail::GAttach;
}
//===============================================
void GEmail::GAttach::setObj(const GEmail::GAttach& _obj) {
    m_file = _obj.m_file;
}
//===============================================
void GEmail::GAttach::addFile(const GString& _file) {
    GAttach* lObj = new GEmail::GAttach;
    lObj->m_file = _file;
    m_map.push_back(lObj);
}
//===============================================
GString GEmail::GAttach::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "file", m_file);
    lDom.addMap(_code, m_map);
    return lDom.toString();
}
//===============================================
void GEmail::GAttach::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_file = lDom.getData(_code, "file");
    lDom.getMap(_code, m_map, this);
}
//===============================================
