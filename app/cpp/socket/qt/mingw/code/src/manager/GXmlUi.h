//===============================================
#ifndef _GXmlUi_
#define _GXmlUi_
//===============================================
#include "GObject.h"
//===============================================
class GXml;
//===============================================
class GXmlUi : public GObject {
    Q_OBJECT

public:
    GXmlUi(QObject* _parent = 0);
    virtual ~GXmlUi();
    static GXmlUi* Create(const QString& _key);
    virtual void run(int _argc, char** _argv);
    void create(GXml& _xml, const std::string& _reference, const std::string& _name, const std::string& _price);
};
//==============================================
#endif
//==============================================