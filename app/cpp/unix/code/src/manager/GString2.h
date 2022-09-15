//===============================================
#ifndef _GString2_
#define _GString2_
//===============================================
#include "GObject.h"
//===============================================
class GString2 : public GObject {
public:
    GString2();
    GString2(const std::string& _data);
    GString2(const char* _data);
    GString2(int _data);
    GString2(const GString2& _data);
    ~GString2();

    GString2& operator=(const GString2& _data);
    GString2& operator=(const std::string& _data);
    GString2& operator=(const char* _data);
    GString2& operator=(int _data);
    //
    GString2& operator+=(const GString2& _data);
    GString2& operator+=(const std::string& _data);
    GString2& operator+=(const char* _data);
    GString2& operator+=(int _data);
    //
    friend GString2 operator+(const GString2& _data1, const GString2& _data2);
    //
    friend std::ostream& operator<<(std::ostream& _os, const GString2& _data);

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
