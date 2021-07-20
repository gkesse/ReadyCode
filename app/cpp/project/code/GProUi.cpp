//===============================================
#include "GProUi.h"
#include "GProList.h"
#include "GProTable.h"
#include "GProAddressKey.h"
#include "GProStack.h"
// page
#include "GProWindow.h"
#include "GProHome.h"
#include "GProLogin.h"
#include "GProSQLite.h"
#include "GProSQLiteTable.h"
#include "GProSQLiteTableButtonUserData.h"
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
    if(key == "table") {return new GProTable;}
    if(key == "addresskey") {return new GProAddressKey;}
    if(key == "stack") {return new GProStack;}
    // page
    if(key == "window") {return new GProWindow;}
    if(key == "home") {return new GProHome;}
    if(key == "login") {return new GProLogin;}
    if(key == "sqlite") {return new GProSQLite;}
    if(key == "sqlitetable") {return new GProSQLiteTable;}
    if(key == "sqlitetable/user_data") {return new GProSQLiteTableButtonUserData;}
    return new GProUi;
}
//===============================================
void GProUi::addPage(QString key, QString title, QWidget* widget, bool isDefault) {}
int GProUi::loadPage() {return 1;}
void GProUi::setPage(QString key) {}
GProUi* GProUi::getPage(QString key) {return 0;}
int GProUi::getPageId(QString key) {return 0;}
QWidget* GProUi::getWidget(QString key) {return 0;}
QString GProUi::getTitle(QString key) {return "";}
QString GProUi::getDefaultKey() {return "";}
void GProUi::addItem(QString key, QString text) {}
void GProUi::setContent(QString text) {}
void GProUi::loadData(QStringList headers, QVector<QVector<QString>> datas) {}
QString GProUi::getKey(const QString& key, const QString& defaultKey) {return "";}
//===============================================
void GProUi::onEvent() {}
void GProUi::onEvent(const QString& text) {}
void GProUi::onEvent(const QPoint& pos) {}
void GProUi::onEvent(int row, int col) {}
void GProUi::onEvent(QTableWidget* tableWidget, int row, int col) {}
//===============================================
