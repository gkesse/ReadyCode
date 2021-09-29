//===============================================
#ifndef _GSocketUi_
#define _GSocketUi_
//===============================================
#include "GInclude.h"
//===============================================
class GSocketUi : public QObject {
	Q_OBJECT

public:
	GSocketUi(QObject* parent = 0);
	virtual ~GSocketUi();
	static GSocketUi* Create(const QString& key, QObject* parent = 0);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
