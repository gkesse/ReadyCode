//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GMaster : public GModule {
    Q_OBJECT

public:
    GMaster(QObject* _parent = 0);
    ~GMaster();
    //
    QString serialize(const QString& _code = "server") const;
    void deserialize(const QString& _data, const QString& _code = "server");
    //
    bool onModule(GSocket* _client);
    void onTest(GSocket* _client);
    //
    bool isValidXml(const QString& _data);
    bool isValidReq();

private:
    bool m_validateXml;
    bool m_validateReq;
};
//==============================================
#endif
//==============================================
