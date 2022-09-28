//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
class GCode : public GXml {
public:
    GCode();
    ~GCode();
    //
    void createReq(const QString& _module, const QString& _method);
    bool hasCode();
    bool hasCode(const QString& _code);
    bool hasCode(const QString& _code, const QString& _key);
    bool createCode(const QString& _code);
    //
    bool addData(const QString& _code, const QString& _key, const QString& _value, bool _isCData = false);
    bool addData(const QString& _code, const QString& _key, int _value, bool _isCData = false);
    bool addData(const QString& _code, const QVector<QString>& _datas, bool _isCData = false);
    bool addData(const QString& _code, const QVector<GObject*>& _datas);
    //
    bool getCode(const QString& _code);
    bool getCode(const QString& _code, const QString& _key);
    //
    QString getItem(const QString& _code, const QString& _key);
    QString getItem(const QString& _code, int _index);
    QString getItem(const QString& _code, const QString& _key, int _index);
    QString getItem(const QString& _code, const QString& _category, const QString& _key);
    bool getItem(const QString& _code, QVector<GObject*>& _datas, GObject* _obj);
    QString getMap(const QString& _code, int _index);
    int countItem(const QString& _code);
    //
    bool loadCode(const QString& _data, const QString& _encoding = "UTF-8");
    //
    QString toStringCode(const QString& _code);
    QString toStringData();
};
//==============================================
#endif
//==============================================
