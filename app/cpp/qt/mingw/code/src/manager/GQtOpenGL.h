//===============================================
#ifndef _GQtOpenGL_
#define _GQtOpenGL_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtOpenGL : public GQtWidget {
    Q_OBJECT

public:
    GQtOpenGL(QWidget* _parent = 0);
    ~GQtOpenGL();

public slots:
    void onSendButton();

private:
    QTextEdit* m_textEdit;
};
//==============================================
#endif
//==============================================
