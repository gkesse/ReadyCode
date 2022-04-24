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
    GCode(const QString& _code, QObject* _parent = 0);
    ~GCode();
    //
    void createRequest(const QString& _module, const QString& _method);
    void addParam(const QString& _key, int _value);
    void addParam(const QString& _key, const QString& _value);
    void addSession(const QString& _key, const QString& _value);
    void addPseudo();
    //
    QString getModule();
    QString getMethod();
    //
    void setCode(const QString& _code);
    bool hasCode(const QString& _code);
    bool hasCode(const QString& _code, int _index);
    bool hasCode(const QString& _code, const QString& _key, int _index);
    bool hasCode(const QString& _code, const QString& _key);
    bool hasMap(const QString& _code);
    void createCode();
    void createCode(const QString& _code);
    void createCode(const QString& _code, const QString& _key, const QString& _value);
    void createMap(const QString& _code, const QString& _key, int _value, int _index, bool _isCData = false);
    void createMap(const QString& _code, const QString& _key, const QString& _value, int _index, bool _isCData = false);
    //
    QString getItem(const QString& _code, const QString& _key);
    QString getItem(const QString& _code, const QString& _key, int _index, bool _isCData = false);
    int countItem(const QString& _code);
    int countItem(const QString& _code, const QString& _key);
    //
    void loadCode(const QString& _code);
    //
    QString toStringCode(const QString& _code);
    QString toStringCode(const QString& _code, int _index);
};
//==============================================
#endif
//==============================================
