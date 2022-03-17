//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GXml.h"
//===============================================
class GRequest : public GXml {
    Q_OBJECT

public:
    GRequest(QObject* _parent = 0);
    ~GRequest();
    //
    GRequest& createRequest(const QString& _module, const QString& _method);
    QString getModule();
    QString getMethod();
};
//==============================================
#endif
//==============================================
