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
    void method(void* const _method);
    
protected:
    xmlrpc_c::registry m_registry;
    xmlrpc_c::methodPtr const m_method;
};
//==============================================
#endif
//==============================================
