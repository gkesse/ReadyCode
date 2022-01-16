//===============================================
#ifndef _GQtOpenCVUi_
#define _GQtOpenCVUi_
//===============================================
#include "GQtMainWindow.h"
#include "GQtStackWidget.h"
//===============================================
class GObject;
//===============================================
class GQtOpenCVUi : public GQtMainWindow {
    Q_OBJECT

public:
    GQtOpenCVUi(QWidget* _parent = 0);
    ~GQtOpenCVUi();
    //
    void createDoms();
    //
    void createCentralWidget();
    //
    QWidget* createTestPage();
    QWidget* createTestLoadPage();
    int countTestPageButtons() const;
    QString getTestPageButtonName(int _index) const;
    QString getTestPageButtonKey(int _index) const;
    QString getTestPageXmlFilename() const;
    std::string sendTestMessage();
    std::string loadTestMessage();
    std::string clearXmlMessage();
    //
    std::string stopMasterServer();
    //
    std::string runOpenCV();
    std::string stopOpenCV();
    std::string clearWindowId();
    //
    std::string openImageFile();

public slots:
    void onMenuAction(bool _checked = false);
    void onEvent();

protected:
    void closeEvent(QCloseEvent *event);

private:
    GQtStackWidget* m_pageMap;
};
//==============================================
#endif
//==============================================
