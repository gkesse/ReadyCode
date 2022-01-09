//===============================================
#ifndef _GQtOpenCVUi_
#define _GQtOpenCVUi_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GObject;
//===============================================
class GQtOpenCVUi : public GQtMainWindow {
    Q_OBJECT

public:
    GQtOpenCVUi(QWidget* _parent = 0);
    ~GQtOpenCVUi();
    void createDoms();
    void createCentralWidget();
    //
    void runOpenCV();
    void stopOpenCV();

public slots:
    void onMenuAction(bool _checked = false);

protected:
    void closeEvent(QCloseEvent *event);

private:
    QSharedPointer<GObject> m_request;
};
//==============================================
#endif
//==============================================
