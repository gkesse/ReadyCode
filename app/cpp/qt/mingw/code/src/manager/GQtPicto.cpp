//===============================================
#include "GQtPicto.h"
//===============================================
GQtPicto* GQtPicto::m_instance = 0;
//===============================================
GQtPicto::GQtPicto(QObject* _parent) : GQtObject(_parent) {
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
QIcon GQtPicto::getPicto(const QString& _picto, const QColor& _color) {
    QVariantMap lOptions;
    lOptions.insert("color" , _color);
    lOptions.insert("color-active" , _color);
    lOptions.insert("color-disabled" , _color);
    lOptions.insert("color-selected" , _color);
    return m_QtAwesome->icon(_picto, lOptions);
}
//===============================================
QIcon GQtPicto::getPictoId(int _picto, const QColor& _color) {
    QVariantMap lOptions;
    lOptions.insert("color" , _color);
    lOptions.insert("color-active" , _color);
    lOptions.insert("color-disabled" , _color);
    lOptions.insert("color-selected" , _color);
    return m_QtAwesome->icon(_picto, lOptions);
}
//===============================================
