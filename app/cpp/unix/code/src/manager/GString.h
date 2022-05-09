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
    GString(const GString& _data);
    ~GString();
    //
    std::vector<std::string> splitData(char _sep) const;
    std::string trimData() const;
    int toInt() const;
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
