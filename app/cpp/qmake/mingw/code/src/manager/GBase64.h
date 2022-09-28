//===============================================
#ifndef _GBase64_
#define _GBase64_
//===============================================
#include "GObject2.h"
//===============================================
class GBase64 : public GObject2 {
public:
    GBase64();
    GBase64(const GString& _data);
    ~GBase64();
    GString encodeData() const;
    GString decodeData() const;

private:
    GString m_data;
};
//==============================================
#endif
//==============================================
