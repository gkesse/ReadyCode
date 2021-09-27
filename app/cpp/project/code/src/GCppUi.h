//===============================================
#ifndef _GCppUi_
#define _GCppUi_
//===============================================
#include "GInclude.h"
//===============================================
class GCppUi : public QObject {
	Q_OBJECT

public:
	GCppUi(QObject* parent = 0);
	virtual ~GCppUi();
	static GCppUi* Create(const QString& key, QObject* parent = 0);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
