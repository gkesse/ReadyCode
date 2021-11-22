//===============================================
#ifndef _GXmlUi_
#define _GXmlUi_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
//===============================================
class GXmlUi {
public:
    GXmlUi();
    virtual ~GXmlUi();
    static GXmlUi* Create(const QString& _key);
    virtual void run(int _argc, char** _argv);
    void append(GXml& _xml, const std::string& _reference, const std::string& _name, const std::string& _price);
};
//==============================================
#endif
//==============================================
