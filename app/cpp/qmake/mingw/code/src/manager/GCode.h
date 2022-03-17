//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
class GCode : public GXml {
    Q_OBJECT

public:
    GCode(QObject* _parent = 0);
    ~GCode();
    //
    bool hasCode(const QString& _code);
    bool hasCode(const QString& _code, const QString& _key);
    void createCode();
    void createCode(const QString& _code);
    void createCode(const QString& _code, const QString& _key, const QString& _value);
    void createMap(const QString& _code, const QString& _key);
    void createMap(const QString& _code, const QString& _key, const QString& _name, const QString& _value);
};
//==============================================
#endif
//==============================================
