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
    void serialize();
    void getRequestList();

private:
    int m_id;
    QString m_module;
    QString m_method;
    QString m_msg;
    //
    std::vector<GRequest> m_reqs;
    std::vector<std::string> m_headers;
};
//==============================================
#endif
//==============================================
