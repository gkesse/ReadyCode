//===============================================
#include "GPicto.h"
//===============================================
GPicto* GPicto::m_instance = 0;
//===============================================
GPicto::GPicto(QObject* _parent) :
GObject(_parent) {
    m_QtAwesome = new QtAwesome(qApp);
    m_QtAwesome->initFontAwesome();
}
//===============================================
GPicto::~GPicto() {

}
//===============================================
GPicto* GPicto::Instance() {
    if(m_instance == 0) {
        m_instance = new GPicto;
    }
    return m_instance;
}
//===============================================
QIcon GPicto::getPicto(const QString& _picto, const QColor& _color) {
    QVariantMap lOptions;
    lOptions.insert("color" , _color);
    lOptions.insert("color-active" , _color);
    lOptions.insert("color-disabled" , _color);
    lOptions.insert("color-selected" , _color);
    return m_QtAwesome->icon(_picto, lOptions);
}
//===============================================
QIcon GPicto::getPictoId(int _picto, const QColor& _color) {
    QVariantMap lOptions;
    lOptions.insert("color" , _color);
    lOptions.insert("color-active" , _color);
    lOptions.insert("color-disabled" , _color);
    lOptions.insert("color-selected" , _color);
    return m_QtAwesome->icon(_picto, lOptions);
}
//===============================================
