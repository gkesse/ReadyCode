//===============================================
#ifndef _GMd5_
#define _GMd5_
//===============================================
#include "GManager.h"
//===============================================
class GMd5 : public GManager {
public:
    GMd5();
    ~GMd5();

    GString encodeData(const GString& _data) const;
};
//==============================================
#endif
//==============================================
