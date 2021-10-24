//===============================================
#ifndef _GXmlRpc_
#define _GXmlRpc_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GXmlRpc {
public:
    GXmlRpc();
    ~GXmlRpc();
    void method(xmlrpc_c::method* _method);
    
protected:
    xmlrpc_c::registry m_registry;
    std::shared_ptr<xmlrpc_c::method> m_method;
};
//==============================================
#endif
//==============================================
