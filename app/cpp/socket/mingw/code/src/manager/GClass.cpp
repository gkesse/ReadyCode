//===============================================
#include "GClass.h"
//===============================================
GClass::GClass() {

}
//===============================================
GClass::~GClass() {

}
//===============================================
void GClass::addObserver(GClass* _obs) {
    m_obs.push_back(_obs);
}
//===============================================
void GClass::notify() {
    for(size_t i = 0; i < m_obs.size(); i++) {
        GClass* lObs = m_obs.at(i);
        lObs->update();
    }
}
//===============================================
void GClass::on() {}
void GClass::update() {}
//===============================================
