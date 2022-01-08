//===============================================
#include "GString.h"
#include "GLog.h"
//===============================================
GString::GString() : GObject() {
    m_data = "";
}
//===============================================
GString::GString(const std::string& _data) : GObject() {
    m_data = _data;
}
//===============================================
GString::GString(int _data) : GObject(){
    m_data = std::to_string(_data);
}
//===============================================
GString::GString(const char* _data, int _size) : GObject() {
    m_data = "";
    for(int i = 0; i < _size; i++) {
        m_data += _data[i];
    }
}
//===============================================
GString::GString(const GString& _data) : GObject() {
    m_data = _data.m_data;
}
//===============================================
GString::~GString() {

}
//===============================================
void GString::addData(const char* _data, int _size) {
    for(int i = 0; i < _size; i++) {
        m_data += _data[i];
    }
}
//===============================================
void GString::clearData() {
    m_data = "";
}
//===============================================
std::string GString::getData() const {
    return m_data;
}
//===============================================
std::vector<std::string> GString::splitData(char _sep) const {
    std::vector<std::string> lDataOut;
    std::istringstream lStream(m_data);
    std::string lData;
    while (std::getline(lStream, lData, _sep)) {
        lDataOut.push_back(lData);
    }
    return lDataOut;
}
//===============================================
std::string GString::trimData() const {
    std::string lData = m_data;
    lData.erase(lData.find_last_not_of(' ') + 1);
    lData.erase(0, lData.find_first_not_of(' '));
    return lData;
}
//===============================================
cv::Scalar GString::getRgb() const {
    std::vector<std::string> lData = splitData(';');

    if(lData.size() == 3) {
        int lRed = std::stoi(lData.at(0));
        int lGreen = std::stoi(lData.at(1));
        int lBlue = std::stoi(lData.at(2));
        return CV_RGB(lRed, lGreen, lBlue);
    }

    return cv::Scalar(0);
}
//===============================================
const char* GString::c_str() const {
    return m_data.c_str();
}
//===============================================
void GString::toChar(char* _buffer, int _size) const {
    int i = 0;
    while(1) {
        if(i >= _size) break;
        if(m_data[i] == 0) break;
        _buffer[i] = m_data[i];
        i++;
    }
    _buffer[i] = 0;
}
//===============================================
int GString::toChar(char* _buffer, int _index, int _size) const {
    int i = 0;
    while(1) {
        if(i >= _size) break;
        if(m_data[i + _index] == 0) break;
        _buffer[i] = m_data[i + _index];
        i++;
    }
    _buffer[i] = 0;
    return i;
}
//===============================================
GString& GString::operator+=(const GString& _data) {
    m_data += _data.m_data;
    return *this;
}
//===============================================
GString operator+(const GString& _data1, const GString& _data2) {
    GString d(_data1);
    d += _data2;
    return d;
}
//===============================================
std::ostream& operator<<(std::ostream& _os, const GString& _data) {
    _os << _data.m_data;
    return _os;
}
//===============================================
