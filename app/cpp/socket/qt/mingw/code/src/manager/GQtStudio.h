//===============================================
#ifndef _GQtStudio_
#define _GQtStudio_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtXml;
//===============================================
class GQtStudio : public GQtMainWindow {
    Q_OBJECT

public:
    GQtStudio(QWidget* _parent = 0);
    ~GQtStudio();
    void createDoms();
    void createActions();
    QString getTitle() const;
    int getWidth() const;
    int getHeight() const;

private:
    QSharedPointer<GQtXml> m_dom;
};
//==============================================
#endif
//==============================================
