//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GModule.h"
//===============================================
class GRequest : public GModule {
public:
    GRequest();
    ~GRequest();
    QString serialize(const QString& _code = "request") const;
    void deserialize(const QString& _data, const QString& _code = "request");
    //
    int getId() const;
    QString getModule() const;
    QString getMethod() const;
    QString getMsg() const;
    //
    void setDataOffset(int _dataOffset);
    void setDataSize(int _dataSize);
    //
    void getRequestList();

private:
    int m_id;
    QString m_msg;
    int m_dataOffset;
    int m_dataSize;
    int m_dataCount;
};
//==============================================
#endif
//==============================================
