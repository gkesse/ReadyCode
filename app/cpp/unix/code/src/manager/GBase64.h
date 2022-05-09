//===============================================
#ifndef _GBase64_
#define _GBase64_
//===============================================
#include "GObject.h"
//===============================================
class GBase64 : public GObject {
public:
    GBase64();
    GBase64(const std::string& _data);
    ~GBase64();
    std::string encodeData() const;
    std::string decodeData() const;

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
