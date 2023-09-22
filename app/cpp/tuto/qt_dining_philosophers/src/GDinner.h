//===============================================
#ifndef _GDinner_
#define _GDinner_
//===============================================
#include "GInclude.h"
//===============================================
class GPhilosopher;
//===============================================
class GDinner : public QObject {
	Q_OBJECT

public:
	GDinner(QObject* _parent = 0);
	~GDinner();
	void init();

public slots:
	void onStart();
	void onStop();

private:
	QVector<GPhilosopher*> m_philosophers;
};
//===============================================
#endif
//===============================================
