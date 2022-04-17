//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GObject.h"
//===============================================
class GRequest : public GObject {
public:
    GRequest();
    GRequest(const std::string& _msg);
    ~GRequest();
    void loadObj();
    void loadId();
    void saveData();
    void insertData();
    void updateData();

private:
    int m_id;
    std::string m_module;
    std::string m_method;
    std::string m_msg;
};
//==============================================
#endif
//==============================================
