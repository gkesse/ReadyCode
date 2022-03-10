//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GObject.h"
//===============================================
class GString : public GObject {
public:
    GString();
    GString(int _data);
    GString(const std::string& _data);
    GString(const GString& _data);
    ~GString();
    //
    std::string getData() const ;
    const char* getChar() const;
    int getSize() const;
    //
    void addData(const std::string& _data);
    void clearData();

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
