//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GCode.h"
//===============================================
class GRequest : public GCode {
    Q_OBJECT

public:
    GRequest(QObject* _parent = 0);
    GRequest(const QString& _code, QObject* _parent = 0);
    ~GRequest();
    //
    GRequest& createRequest(const QString& _module, const QString& _method);
    QString getModule();
    QString getMethod();
};
//==============================================
#endif
//==============================================
