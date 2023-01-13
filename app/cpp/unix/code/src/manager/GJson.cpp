//===============================================
#include "GJson.h"
//===============================================
GJson::GJson(bool _isFormat) {
    m_current = 0;
    m_parent = 0;
    m_child = 0;
    m_isFormat = _isFormat;
}
//===============================================
GJson::~GJson() {
    clearJson();
}
//===============================================
void GJson::createObject() {
    m_current = json_object_new_object();
}
//===============================================
void GJson::createArray() {
    m_current = json_object_new_array();
}
//===============================================
void GJson::pushObject() {
    if(m_current) {
        m_map.push(m_current);
    }
}
//===============================================
void GJson::popObject() {
    if(!m_map.empty()) {
        m_current = m_map.top();
        m_map.pop();
    }
}
//===============================================
void GJson::initParent() {
    m_parent = m_current;
}
//===============================================
void GJson::initChild() {
    m_child = m_current;
}
//===============================================
void GJson::addData(const GString& _key, const GString& _value) {
    json_object_object_add(m_current, _key.c_str(), json_object_new_string(_value.c_str()));
}
//===============================================
void GJson::addData(const GString& _value) {
    json_object_array_add(m_current, json_object_new_string(_value.c_str()));
}
//===============================================
void GJson::addObject() {
    json_object_array_add(m_parent, m_child);
}
//===============================================
void GJson::addObject(const GString& _key) {
    json_object_object_add(m_parent, _key.c_str(), m_child);
}
//===============================================
void GJson::clearJson() {
    json_object_put(m_current);
}
//===============================================
GString GJson::toString() const {
    GString lData;
    if(m_isFormat) {
        lData = json_object_to_json_string_ext(m_current, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
    }
    else {
        lData = json_object_to_json_string(m_current);
    }
    return lData;
}
//===============================================
