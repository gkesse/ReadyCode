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
    void createClipboard();
    void setCurrentFile(const QString& _filename = "");
    void setPosition(QWidget* _parent);
    void createWindowTitle();
    void openFile(const QString& _filename);
    void loadFile(const QString& _filename);
    GQtSdi* findMainWindow(const QString &fileName) const;
    bool saveFile(const QString& _filename);
    bool save();
    bool saveAs();
    bool maybeSave();
    void writeSettings();
    void setLanguage(const QString& _lang);
    void setLanguageIndex(const QString& _key);

protected:
    void closeEvent(QCloseEvent* _event);

public slots:
    void onMenuAction();
    void onMenuBox();
    void onMenuBoxAction();
    void onBoxRecentFile();
    void onTextEditChange();

private:
    QTextEdit* m_textEdit;
    static int m_documentCount;
    bool m_untitled;
    QString m_currentFile;
};
//==============================================
#endif
//==============================================
