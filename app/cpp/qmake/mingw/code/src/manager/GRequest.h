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
    std::vector<GRequest> m_reqMap;
};
//==============================================
#endif
//==============================================
