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
    std::string getData() const ;
    const char* c_str() const;
    void toChar(char* buffer) const;
    void print() const;

public:
    friend std::ostream& operator<<(std::ostream& os, const GString& obj);

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
