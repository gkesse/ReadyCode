//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GObject.h"
//===============================================
class GString : public GObject {
public:
    GString();
    GString(const std::string& _data);
    GString(int _data);
    GString(const char* _data, int _size);
    GString(const GString& _data);
    ~GString();
    //
    void addData(const char* _data, int _size);
    void clearData();
    std::string getData() const ;
    //
    std::vector<std::string> splitData(char _sep) const;
    std::string trimData() const;
    //
    cv::Scalar getRgb() const ;
    //
    const char* c_str() const;
    void toChar(char* _buffer, int _size) const;
    int toChar(char* _buffer, int _index, int _size) const;
    //
    GString& operator+=(const GString& _data);
    friend GString operator+(const GString& _data1, const GString& _data2);
    friend std::ostream& operator<<(std::ostream& _os, const GString& _data);

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
