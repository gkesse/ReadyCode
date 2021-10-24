//===============================================
#ifndef _GXmlRpcM_
#define _GXmlRpcM_
//===============================================
#include "GInclude.h"
//===============================================
class GXmlRpcM : public public xmlrpc_c::method {
public:
	typedef xmlrpc_c::paramList pList;
	typedef xmlrpc_c::value pValue;
	typedef void (*onExecuteCB)(const pList _params, const pValue* _value);

public:
    GXmlRpcM();
    ~GXmlRpcM();
    void signature(const std::string _signature);
    void help(const std::string _help);
    void onExecute(onExecuteCB _onExecute);

protected:
    void execute(const pList _params, const pValue* _value);

protected:
    onExecuteCB m_onExecute;
};
//==============================================
#endif
//==============================================
