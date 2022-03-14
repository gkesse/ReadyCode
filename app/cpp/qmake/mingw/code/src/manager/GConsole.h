//===============================================
#ifndef _GConsole_
#define _GConsole_
//===============================================
#include "GObject.h"
//===============================================
#define GCONSOLEI GConsole::Instance()
#define console GCONSOLEI->printData
//===============================================
class GConsole : public GObject {
	Q_OBJECT

public:
    GConsole(QObject* _parent = 0);
    ~GConsole();
    static GConsole* Instance();
    void printData(const QString& _data);

private:
    static GConsole* m_instance;
};
//==============================================
#endif
//==============================================
