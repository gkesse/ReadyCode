//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
class GString {
public:
    GString();
    ~GString();
    void setData(int data);
    void setData(const std::string& data);
    void setData(const char* data, int size);
    void addData(const char* data, int size);
    void clear();
    std::string str() const ;
    int size() const ;
    const char* c_str() const;
    int toChar(char* buffer, int size) const;
    int toChar(char* buffer, int index, int size) const;
    void print() const;

public:
    friend std::ostream& operator<<(std::ostream& os, const GString& obj);

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
