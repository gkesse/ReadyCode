//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
class GString {
public:
    GString();
    GString(const std::string& _data);
    GString(int _data);
    GString(const char* _data, int _size);
    GString(const GString& _data);
    ~GString();
    void add(const char* _data, int _size);
    void clear();
    std::string datas() const ;
    const char* c_str() const;
    void toChar(char* _buffer, int _size) const;
    int toChar(char* _buffer, int _index, int _size) const;
    GString& operator+=(const GString& _d);
    friend GString operator+(const GString& _d1, const GString& _d2);
    friend std::ostream& operator<<(std::ostream& _os, const GString& _d);

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
