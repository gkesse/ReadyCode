//===============================================
#ifndef _GQtOpenCVUi_
#define _GQtOpenCVUi_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GObject;
class GQtStackWidget;
class GRequest;
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
    std::string loadXmlMessage();
    //
    std::string stopMasterServer();
    //
    std::string runOpenCV();
    std::string stopOpenCV();
    std::string clearWindowId();
    //
    std::string openImageFile();
    //
    void onLoadXmlMessage(const GRequest& _req);


public slots:
    void onMenuAction(bool _checked = false);
    void onEvent();
    void onEvent(QTreeWidgetItem *item, int column);

protected:
    void closeEvent(QCloseEvent *event);

private:
    GQtStackWidget* m_pageMap;
};
//==============================================
#endif
//==============================================
