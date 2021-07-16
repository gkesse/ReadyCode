//===============================================
#include "GSQLite.h"
#include "GManager.h"
//===============================================
GSQLite* GSQLite::m_instance = 0;
//===============================================
GSQLite::GSQLite() {
    open();
    // users
    writeData(QString(""
    "create table if not exists users (\n"
    "username text,\n"
    "password text\n"
    ")\n"
    ""));
    // read
    qDebug() << readData(QString(""
    "select name from sqlite_master\n"
    ""));
}
//===============================================
GSQLite::~GSQLite() {

}
//===============================================
GSQLite* GSQLite::Instance() {
    if(m_instance == 0) {
        m_instance = new GSQLite;
    }
    return m_instance;
}
//===============================================
void GSQLite::open() {
    sGApp* lApp = GManager::Instance()->getData()->app;
    if(QSqlDatabase::isDriverAvailable(lApp->sqlite_driver)) {
        QSqlDatabase lDb = QSqlDatabase::addDatabase(lApp->sqlite_driver);
        lDb.setDatabaseName(lApp->sqlite_db_path);
        if(!lDb.open()) {
            qDebug() << "[sqlite] erreur ouverture bdd : " << lDb.lastError();
        }
    }
    else {
        qDebug() << "[sqlite] erreur driver indisponible";
    }
}
//===============================================
void GSQLite::writeData(const QString& sql) {
    QSqlQuery lQuery(sql);
    if(!lQuery.isActive()) {
        qDebug() << "[sqlite] erreur ecriture donnees";
    }
}
//===============================================
QString GSQLite::readData(const QString& sql) {
    QSqlQuery lQuery(sql);
    if(!lQuery.isActive()) {
        qDebug() << "[sqlite] erreur ecriture donnees";
    }
    QString lData = "";
    if(lQuery.first()) {
        lData = lQuery.value(0).toString();
    }
    return lData;
}
//===============================================
