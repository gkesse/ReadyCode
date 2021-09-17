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
    void addPage(const QString& key, const QString& title, QWidget* widget, bool isDefault = 0);
    void setPage(const QString& key);
    void setTitle(const QString& key, const QString& title);
    QString getKey(const QString& key, const QString& defaultKey);
    GProUi* getPage(const QString& key);
    int getPageId(const QString& key);
    QWidget* getWidget(const QString& key);
    QString getTitle(const QString& key);
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
