//===============================================
#ifndef _GSocketUi_
#define _GSocketUi_
//===============================================
#include "GObject.h"
//===============================================
class GSocketUi : public GObject {
    Q_OBJECT

public:
    GSocketUi(QObject* _parent = 0);
    virtual ~GSocketUi();
    static GSocketUi* Create(const QString& key, QObject* _parent = 0);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================