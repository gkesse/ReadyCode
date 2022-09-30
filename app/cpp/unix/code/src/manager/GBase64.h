//===============================================
#ifndef _GBase64_
#define _GBase64_
//===============================================
#include "GObject.h"
//===============================================
class GBase64 : public GObject {
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
