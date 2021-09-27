//===============================================
#ifndef _GQtUi_
#define _GQtUi_
//===============================================
#include "GInclude.h"
//===============================================
class GQtUi : public QObject {
	Q_OBJECT

public:
	GQtUi(QObject* parent = 0);
	virtual ~GQtUi();
	static GQtUi* Create(const QString& key, QObject* parent = 0);
    virtual void run(int argc, char** argv);

public slots:
	void onStart();
	void onReady();
	void onReadyError();
	void onError(QProcess::ProcessError error);
	void onEvent(const QString& text);
};
//==============================================
#endif
//==============================================
