//===============================================
#ifndef _GStyle_
#define _GStyle_
//===============================================
#include "GObject.h"
//===============================================
#define GSTYLEI GStyle::Instance()
#define GSTYLE(x) GSTYLEI->loadStyle(x)
//===============================================
class GStyle : public GObject {
	Q_OBJECT

public:
    GStyle(QObject* _parent = 0);
    ~GStyle();
    static GStyle* Instance();
    void loadStyle(const QString& _filename);

private:
    static GStyle* m_instance;
};
//==============================================
#endif
//==============================================
