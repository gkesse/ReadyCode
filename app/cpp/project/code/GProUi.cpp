//===============================================
#include "GProUi.h"
#include "GProList.h"
#include "GProTable.h"
#include "GProAddressKey.h"
#include "GProStack.h"
#include "GProTitle.h"
// page
#include "GProWindow.h"
#include "GProHome.h"
#include "GProLogin.h"
#include "GProSQLite.h"
#include "GProSQLiteTable.h"
#include "GProSQLiteTableUserDataButton.h"
#include "GProSQLiteTableUserDataAdd.h"
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
    if(key == "title") {return new GProTitle;}
    // page
    if(key == "window") {return new GProWindow;}
    if(key == "home") {return new GProHome;}
    if(key == "login") {return new GProLogin;}
    if(key == "sqlite") {return new GProSQLite;}
    if(key == "sqlitetable") {return new GProSQLiteTable;}
    if(key == "sqlitetable/user_data/button") {return new GProSQLiteTableUserDataButton;}
    if(key == "sqlitetable/user_data/add") {return new GProSQLiteTableUserDataAdd;}
    return new GProUi;
}
//===============================================
void GProUi::addPage(const QString& key, const QString& title, QWidget* widget, bool isDefault) {}
int GProUi::loadPage(const QString& key) {return 1;}
void GProUi::setPage(const QString& key) {}
GProUi* GProUi::getPage(const QString& key) {return 0;}
int GProUi::getPageId(const QString& key) {return 0;}
QWidget* GProUi::getWidget(const QString& key) {return 0;}
QString GProUi::getTitle(const QString& key) {return "";}
QString GProUi::getDefaultKey() {return "";}
void GProUi::addItem(const QString& key, const QString& text) {}
void GProUi::setContent(const QString& text) {}
void GProUi::loadData(const QStringList& headers, const QVector<QVector<QString>>& datas) {}
QString GProUi::getKey(const QString& key, const QString& defaultKey) {return "";}
void GProUi::setTitle(const QString& text) {}
void GProUi::setTitle(const QString& key, const QString& title) {}
//===============================================
void GProUi::onEvent() {}
void GProUi::onEvent(const QString& text) {}
void GProUi::onEvent(const QPoint& pos) {}
void GProUi::onEvent(int row, int col) {}
void GProUi::onEvent(QTableWidget* tableWidget, int row, int col) {}
//===============================================
