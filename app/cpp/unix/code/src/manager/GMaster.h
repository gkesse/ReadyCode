//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GMaster : public GObject {
public:
    GMaster();
    ~GMaster();
    void onModuleMaster(std::string _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
