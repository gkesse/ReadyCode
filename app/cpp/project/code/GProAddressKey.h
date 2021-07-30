//===============================================
#ifndef _GProAddressKey_
#define _GProAddressKey_
//===============================================
#include "GProUi.h"
//===============================================
class GProAddressKey : public GProUi {
    Q_OBJECT

public:
    GProAddressKey(QWidget* parent = 0);
    ~GProAddressKey();
    
public:
    void setAddress(const QString& text);

public slots:
    void onEvent();
    
private:
    QHBoxLayout* m_mainLayout;
    QMap<QWidget*, QString> m_widgetMap;
};
//===============================================
#endif
//===============================================
