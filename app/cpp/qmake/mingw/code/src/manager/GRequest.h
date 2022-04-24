//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GObject.h"
//===============================================
class GRequest : public GObject {
    Q_OBJECT

public:
    GRequest(QObject* _parent = 0);
    ~GRequest();
    void clearReqs();
    //
    int getId() const;
    QString getModule() const;
    QString getMethod() const;
    QString getMsg() const;
    QVector<GRequest*>& getReqs();
    QVector<QString>& getHeaders();
    //
    QString serialize() const;
    void deserializeMap(const QString& _data);
    void getRequestList();

private:
    int m_id;
    QString m_module;
    QString m_method;
    QString m_msg;
    //
    QVector<GRequest*> m_reqs;
    QVector<QString> m_headers;
};
//==============================================
#endif
//==============================================
