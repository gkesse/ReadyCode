//===============================================
#include "GPhilosopher.h"
//===============================================
GPhilosopher::GPhilosopher(QObject* _parent)
: QObject(_parent) {

}
//===============================================
GPhilosopher::~GPhilosopher() {

}
//===============================================
void GPhilosopher::process() {
	while(!m_stopFlag.load()) {

	}
}
//===============================================
void GPhilosopher::onStart() {
	printf("%s...\n", __PRETTY_FUNCTION__);
	m_stopFlag.store(false);
	process();
}
//===============================================
void GPhilosopher::onStop() {
	printf("%s...\n", __PRETTY_FUNCTION__);
}
//===============================================
