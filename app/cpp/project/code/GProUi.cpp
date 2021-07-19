//===============================================
#include "GProUi.h"
#include "GProList.h"
#include "GProStack.h"
#include "GProWindow.h"
#include "GProHome.h"
#include "GProLogin.h"
//===============================================
GProUi::GProUi(QWidget* parent) :
QFrame(parent) {

}
//===============================================
GProUi::~GProUi() {

}
//===============================================
GProUi* GProUi::Create(const QString& key) {
    if(key == "default") {return new GProUi;}
    if(key == "list") {return new GProList;}
    if(key == "stack") {return new GProStack;}
    if(key == "window") {return new GProWindow;}
    if(key == "home") {return new GProHome;}
    if(key == "login") {return new GProLogin;}
    return new GProUi;
}
//===============================================
void GProUi::onEvent(const QString& event) {}
void GProUi::addPage(QString key, QString title, QWidget* widget, bool isDefault) {}
int GProUi::loadPage() {return 1;}
void GProUi::setPage(QString key) {}
GProUi* GProUi::getPage(QString key) {return 0;}
int GProUi::getPageId(QString key) {return 0;}
QWidget* GProUi::getWidget(QString key) {return 0;}
QString GProUi::getTitle(QString key) {return "";}
QString GProUi::getDefaultKey() {return "";}
void GProUi::addItem(QString key, QString text) {}
//===============================================
void GProUi::slotEvent() {}
void GProUi::slotEvent(const QString& text) {}
void GProUi::slotEvent(const QPoint& pos) {}
void GProUi::slotEvent(int row, int col) {}
//===============================================
