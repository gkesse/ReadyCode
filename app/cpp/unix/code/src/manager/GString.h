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
    GString(const char* _data);
    GString(int _data);
    GString(const GString& _data);
    ~GString();
    //
    std::string data() const;
    const char* c_str() const;
    //
    std::vector<std::string> splitData(char _sep) const;
    std::string trimData() const;
    int toInt() const;
    bool toBool() const;
    //
    GString& operator=(const GString& _data);
    GString& operator=(const std::string& _data);
    GString& operator=(const char* _data);
    GString& operator=(int _data);
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
