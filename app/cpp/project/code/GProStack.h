//===============================================
#ifndef _GProStack_
#define _GProStack_
//===============================================
#include "GProUi.h"
//===============================================
class GProStack : public GProUi {
    Q_OBJECT

public:
    GProStack(QWidget* parent = 0);
    ~GProStack();

public:
    void addPage(QString key, QString title, QWidget* widget, bool isDefault = 0);
    void setPage(QString key);
    GProUi* getPage(QString key);
    int getPageId(QString key);
    QWidget* getWidget(QString key);
    QString getTitle(QString key);
    QString getDefaultKey();
    
protected:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private:
    QStackedWidget* m_workspace;
    QMap<QString, int> m_pageId;
    QMap<QString, QString> m_titleMap;
    bool m_defaultKeyFlag;
    QString m_defaultKey;
};
//===============================================
#endif
//===============================================
