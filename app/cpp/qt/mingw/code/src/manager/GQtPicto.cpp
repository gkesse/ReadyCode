//===============================================
#include "GQtPicto.h"
//===============================================
GQtPicto* GQtPicto::m_instance = 0;
//===============================================
GQtPicto::GQtPicto() {
    m_QtAwesome = new QtAwesome(qApp);
    m_QtAwesome->initFontAwesome();
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
QIcon GQtPicto::getPicto(int _picto, const QColor& _color) {
    QVariantMap lOptions;
    lOptions.insert("color-active" , _color);
    return m_QtAwesome->icon(_picto);
}
//===============================================
