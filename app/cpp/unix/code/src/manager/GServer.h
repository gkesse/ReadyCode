//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GModule2.h"
//===============================================
class GServer : public GModule2 {
public:
    GServer();
    ~GServer();

    void setApiKey(const GString2& _apiKey);
    void run(int _argc, char** _argv);
    static void* onThreadCB(void* _params);
    bool onReadyApp();
    bool isReadyApp();
    bool readData();

private:
    static const int BUFFER_SIZE = 1024;
    static const char* API_KEY = "API_KEY";
    GString2 m_apiKey;
    int m_size;
    int m_dSize;
};
//==============================================
#endif
//==============================================
