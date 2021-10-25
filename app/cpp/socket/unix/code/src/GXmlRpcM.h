//===============================================
#ifndef _GXmlRpcM_
#define _GXmlRpcM_
//===============================================
#include "GInclude.h"
//===============================================
class GXmlRpcM : public xmlrpc_c::method {
public:
	typedef xmlrpc_c::paramList const& pList;
	typedef xmlrpc_c::value* const pValue;
	typedef void (*onExecuteCB)(pList _params, pValue _value);

public:
    GXmlRpcM();
    ~GXmlRpcM();
    void signature(const std::string _signature);
    void help(const std::string _help);
    void onExecute(onExecuteCB _onExecute);

protected:
    void execute(pList _params, pValue _value);

protected:
    onExecuteCB m_onExecute;
};
//==============================================
#endif
//==============================================
