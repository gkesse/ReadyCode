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
    static GXmlUi* Create(const QString& key);
    virtual void run(int _argc, char** _argv);
    void create(GXml& _dom, GXml& _child, const QString& _name);
    void create(GXml& _dom, GXml& _child, const QString& _reference, const QString& _name, const QString& _price);
};
//==============================================
#endif
//==============================================
