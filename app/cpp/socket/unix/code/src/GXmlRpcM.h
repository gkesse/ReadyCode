//===============================================
#ifndef _GXmlRpcM_
#define _GXmlRpcM_
//===============================================
#include "GInclude.h"
//===============================================
class GXmlRpcM : public public xmlrpc_c::method {
public:
    GXmlRpcM();
    ~GXmlRpcM();
    void signature(const std::string _signature);
    void help(const std::string _help);
};
//==============================================
#endif
//==============================================
