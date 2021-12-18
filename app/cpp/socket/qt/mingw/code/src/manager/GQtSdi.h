//===============================================
#ifndef _GQtSdi_
#define _GQtSdi_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtXml;
//===============================================
class GQtSdi : public GQtMainWindow {
    Q_OBJECT

public:
    GQtSdi(QWidget* _parent = 0);
    ~GQtSdi();
    void createDoms();
    void createCentralWidget();
    void createWindowTitle(const QString& _filename = "");
    void setPosition(QWidget* _parent);

public slots:
    void onMenuAction();
    void onTextEditChange();

private:
    QTextEdit* m_textEdit;
    static int m_documentCount;
};
//==============================================
#endif
//==============================================
