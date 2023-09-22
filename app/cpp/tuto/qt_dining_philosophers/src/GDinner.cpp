//===============================================
#include "GDinner.h"
#include "GPhilosopher.h"
//===============================================
GDinner::GDinner(QObject* _parent)
: QObject(_parent) {

}
//===============================================
GDinner::~GDinner() {

}
//===============================================
void GDinner::init() {
	int lPhiloNum = 5;

	for(int i = 0; i < lPhiloNum; ++i) {
		GPhilosopher* lPhilo = new GPhilosopher;
		m_philosophers.push_back(lPhilo);
	}
}
//===============================================
void GDinner::onStart() {
	printf("%s...\n", __PRETTY_FUNCTION__);
	for(GPhilosopher* lPhilo : m_philosophers) {
		QMetaObject::invokeMethod(lPhilo, "onStart", Qt::QueuedConnection);
	}
}
//===============================================
void GDinner::onStop() {
	printf("%s...\n", __PRETTY_FUNCTION__);
}
//===============================================
