//===============================================
#ifndef _GQtMdiChild_
#define _GQtMdiChild_
//===============================================
#include "GQtTextEdit.h"
//===============================================
class GQtMdiChild : public GQtTextEdit {
    Q_OBJECT

public:
    GQtMdiChild(QWidget* _parent = 0);
    ~GQtMdiChild();
    void newFile(const QString& _title = "");
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile();

private:
    bool maybeSave();
    void setCurrentFile(const QString& _filename);
    QString strippedName(const QString& _fullname);

public slots:
    void documentWasModified();

protected:
    void closeEvent(QCloseEvent* event);

private:
    static int m_sequenceNumber;
    bool isUntitled;
    QString curFile;
};
//==============================================
#endif
//==============================================
