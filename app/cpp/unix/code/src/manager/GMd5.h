//===============================================
#ifndef _GMd5_
#define _GMd5_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GMd5 : public GObject {
public:
    GMd5();
    GMd5(const std::string& _data);
    ~GMd5();
    std::string encodeData() const;

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
