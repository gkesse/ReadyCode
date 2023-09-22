//===============================================
#ifndef _GPhilosopher_
#define _GPhilosopher_
//===============================================
#include "GInclude.h"
//===============================================
class GPhilosopher : public QObject {
	Q_OBJECT

public:
	GPhilosopher(QObject* _parent = 0);
	~GPhilosopher();
	void process();

public slots:
	void onStart();
	void onStop();

private:
	std::atomic<bool> m_stopFlag;
};
//===============================================
#endif
//===============================================
