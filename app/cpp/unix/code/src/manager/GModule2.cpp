//===============================================
#include "GModule2.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket2.h"
//===============================================
GModule2::GModule2()
: GObject() {
    m_client = 0;
}
//===============================================
GModule2::~GModule2() {

}
//===============================================
void GModule2::setClient(GSocket2* _client) {
    m_client = _client;
}
//===============================================
