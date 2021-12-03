//===============================================
#include "GQtPicto.h"
#include "GQt.h"
#include "GQtLog.h"
//===============================================
GQtPicto* GQtPicto::m_instance = 0;
//===============================================
GQtPicto::GQtPicto() {
    m_QtAwesome = new QtAwesome(qApp);
    m_QtAwesome->initFontAwesome();
    m_QtAwesome-> setDefaultOption("color-active" , "white");
}
//===============================================
GQtPicto::~GQtPicto() {

}
//===============================================
GQtPicto* GQtPicto::Instance() {
    if(m_instance == 0) {
        m_instance = new GQtPicto;
    }
    return m_instance;
}
//===============================================
void GQtPicto::setPicto(const QColor& _color) {
    m_QtAwesome-> setDefaultOption("color-active" , _color);
}
//===============================================
QIcon GQtPicto::getPicto(int _picto) {
    return m_QtAwesome->icon(_picto);
}
//===============================================
QIcon GQtPicto::getPictoColor(int _picto, const QColor& _color) {
    QVariantMap lOptions;
    lOptions.insert("color-active" , _color);
    return m_QtAwesome->icon(_picto);
}
//===============================================
