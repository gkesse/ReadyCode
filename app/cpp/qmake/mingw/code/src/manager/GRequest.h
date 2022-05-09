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
    void setDataOffset(int _dataOffset);
    void setDataSize(int _dataSize);
    //
    QString serialize() const;
    void deserializeMap(const QString& _data);
    void getRequestList();

private:
    int m_id;
    QString m_module;
    QString m_method;
    QString m_msg;
    int m_dataOffset;
    int m_dataSize;
    //
    QVector<GRequest*> m_reqs;
    QVector<QString> m_headers;
};
//==============================================
#endif
//==============================================
