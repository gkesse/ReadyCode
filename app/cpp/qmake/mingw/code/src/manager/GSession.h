//===============================================
#ifndef _GSession_
#define _GSession_
//===============================================
#include "GObject.h"
//===============================================
class GSession : public GObject {
public:
    GSession();
    ~GSession();
    GString serialize() const;
    void deserialize(const GString& _data);

protected:
    int m_userId;
};
//==============================================
#endif
//==============================================
