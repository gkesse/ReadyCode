//===============================================
#ifndef _GCvUi_
#define _GCvUi_
//===============================================
#include "GWidget.h"
//===============================================
class GCvUi : public GWidget {
    Q_OBJECT

public:
    GCvUi(QWidget* _parent = 0);
    ~GCvUi();
    void createLayout();
    void onConnect();
    void onUsernameClear();
    void onUsernameClear(const QString& _text);
    void onPasswordClear();
    void onPasswordClear(const QString& _text);

public slots:
    void onEvent();
    void onEvent(const QString& _text);
};
//===============================================
#endif
//===============================================
