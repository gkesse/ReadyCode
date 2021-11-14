//===============================================
#ifndef _GSocketServer_
#define _GSocketServer_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketServer : public GSocketUi {
    Q_OBJECT

public:
    GSocketServer(QObject* _parent = 0);
    ~GSocketServer();
    void run(int _argc, char** _argv);
    static DWORD WINAPI onStart(LPVOID _params);
};
//==============================================
#endif
//==============================================
