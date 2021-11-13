//===============================================
#ifndef _GSocketClient_
#define _GSocketClient_
//===============================================
#include "GSocketUi.h"
//===============================================
class GSocketClient : public GSocketUi {
    Q_OBJECT

public:
    GSocketClient(QObject* _parent = 0);
    ~GSocketClient();
    void run(int _argc, char** _argv);

public slots:
    void onEvent(const QString& _text);
};
//==============================================
#endif
//==============================================
