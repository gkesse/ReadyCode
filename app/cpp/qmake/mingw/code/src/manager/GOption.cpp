//===============================================
#include "GOption.h"
#include "GCode.h"
#include "GClient.h"
//===============================================
GOption::GOption()
: GObject() {
    m_id = 0;
    m_state = false;
}
//===============================================
GOption::~GOption() {

}
//===============================================
GObject* GOption::clone() const {
    return new GOption;
}
//===============================================
GString GOption::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "state", m_state);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
bool GOption::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GOption::setId(int _id) {
    m_id = _id;
}
//===============================================
void GOption::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
void GOption::setState(bool _state) {
    m_state = _state;
}
//===============================================
bool GOption::getState() const {
    return m_state;
}
//===============================================
std::vector<GObject*>& GOption::getOptionMap() {
    return m_map;
}
//===============================================
const std::vector<GObject*>& GOption::getOptionMap() const {
    return m_map;
}
//===============================================
void GOption::createOption() {
    GString lData = serialize();
    lData = GCALL_SERVER("option", "create_option", lData);
    deserialize(lData);
}
//===============================================
void GOption::enableOption() {
    GString lData = serialize();
    lData = GCALL_SERVER("option", "enable_option", lData);
    deserialize(lData);
}
//===============================================
void GOption::disableOption() {
    GString lData = serialize();
    lData = GCALL_SERVER("option", "disable_option", lData);
    deserialize(lData);
}
//===============================================
void GOption::readOption() {
    GString lData = serialize();
    lData = GCALL_SERVER("option", "read_option", lData);
    deserialize(lData);
}
//===============================================
void GOption::updateOption() {
    GString lData = serialize();
    lData = GCALL_SERVER("option", "update_option", lData);
    deserialize(lData);
}
//===============================================
void GOption::deleteOption() {
    GString lData = serialize();
    lData = GCALL_SERVER("option", "delete_option", lData);
    deserialize(lData);
}
//===============================================
void GOption::searchOption() {
    GString lData = serialize();
    lData = GCALL_SERVER("option", "search_option", lData);
    deserialize(lData);
}
//===============================================
