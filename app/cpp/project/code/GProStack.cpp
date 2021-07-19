//===============================================
#include "GProStack.h"
//===============================================
GProStack::GProStack(QWidget* parent) :
GProUi(parent)  {
    QStackedWidget* lWorkspace = new QStackedWidget;
    m_workspace = lWorkspace;

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addWidget(lWorkspace);
    lMainLayout->setMargin(0);

    setLayout(lMainLayout);

    m_defaultKeyFlag = true;
    m_defaultKey = "";
}
//===============================================
GProStack::~GProStack() {

}
//===============================================
void GProStack::addPage(QString key, QString title, QWidget* widget, bool isDefault) {
    int lPageId = m_workspace->count();
    m_pageId[key] = lPageId;
    m_titleMap[key] = title;
    m_workspace->addWidget(widget);

    if(m_defaultKeyFlag == true) {m_defaultKey = key; m_defaultKeyFlag = false;}

    if(isDefault == 1) {
        m_defaultKey = key;
        setPage(key);
    }
}
//===============================================
void GProStack::setPage(QString key) {
    int lPageId = m_pageId.value(key, -1);
    if(lPageId == -1) {return;}
    getPage(key)->loadPage();
    m_workspace->setCurrentIndex(lPageId);
}
//===============================================
GProUi* GProStack::getPage(QString key) {
    int lPageId = m_pageId.value(key, -1);
    if(lPageId == -1) {return 0;}
    QWidget* lWidget = m_workspace->widget(lPageId);
    GProUi* lPage = qobject_cast<GProUi*>(lWidget);
    return lPage;
}
//===============================================
int GProStack::getPageId(QString key) {
    int lPageId = m_pageId.value(key, -1);
    return lPageId;
}
//===============================================
QWidget* GProStack::getWidget(QString key) {
    int lPageId = m_pageId.value(key, -1);
    if(lPageId == -1) {return 0;}
    QWidget* lWidget = m_workspace->widget(lPageId);
    return lWidget;
}
//===============================================
QString GProStack::getTitle(QString key) {
    QString lTitle = m_titleMap.value(key, "");
    return lTitle;
}
//===============================================
QString GProStack::getDefaultKey() {
    return m_defaultKey;
}
//===============================================
QSize GProStack::sizeHint() const {
    if(m_workspace->count() == 0) return QSize(0, 0);
    return m_workspace->currentWidget()->sizeHint();
}
//===============================================
QSize GProStack::minimumSizeHint() const {
    if(m_workspace->count() == 0) return QSize(0, 0);
    return m_workspace->currentWidget()->minimumSizeHint();
}
//===============================================
