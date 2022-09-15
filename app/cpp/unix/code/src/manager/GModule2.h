//===============================================
#ifndef _GModule2_
#define _GModule2_
//===============================================
#include "GObject.h"
//===============================================
class GSocket2;
//===============================================
class GModule2 : public GObject {
public:
    GModule2();
    virtual ~GModule2();
    void setClient(GSocket2* _client);

protected:
    GSocket2* m_client;
};
//==============================================
#endif
//==============================================
