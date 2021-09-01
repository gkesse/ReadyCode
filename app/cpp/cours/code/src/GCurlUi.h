//===============================================
#ifndef _GCurlUi_
#define _GCurlUi_
//===============================================
#include "GInclude.h"
//===============================================
class GCurlUi : public QObject {
    Q_OBJECT
    
public:
    GCurlUi(QObject* parent = 0);
    virtual ~GCurlUi();
    static GCurlUi* Create(const QString& key);
    virtual void run(int argc, char** argv);
    static size_t onWriteCallback(void* contents, size_t size, size_t nmemb, void* params);
};
//==============================================
#endif
//==============================================
