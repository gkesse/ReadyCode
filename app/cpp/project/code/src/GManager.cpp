//===============================================
#include "GManager.h"
#include "GSQLite.h"
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {
    // manager
    mgr = new sGManager;
    // app
    mgr->app = new sGApp;
    mgr->app->app_name = "ReadyApp";
    mgr->app->sqlite_driver = "QSQLITE";
    mgr->app->sqlite_db_path = "data/sqlite/db/database.dat";
    mgr->app->sqlite_sql_path = "data/sqlite/sql";
    mgr->app->sqlite_sql_master = "data/sqlite/sql/master/master.sh";
    mgr->app->sqlite_sql_tmp = "data/sqlite/sql/tmp/tmp.txt";
    mgr->app->sqlite_table_name = "";
}
//===============================================
GManager::~GManager() {

}
//===============================================
GManager* GManager::Instance() {
    if(m_instance == 0) {
        m_instance = new GManager;
    }
    return m_instance;
}
//===============================================
sGManager* GManager::getData() {
    return mgr;
}
//===============================================
// data
//===============================================
void GManager::setData(QTextEdit* textEdit, const QVector<QString>& data) {
    textEdit->clear();
    for(int i = 0; i < data.size(); i++) {
        QString lData = data.at(i);
        textEdit->append(lData);
    }
}
//===============================================
void GManager::setData(QTextEdit* textEdit, const QVector<QVector<QString>>& data) {
    textEdit->clear();
    for(int i = 0; i < data.size(); i++) {
        QVector<QString> lRow = data.at(i);
        QString lLine = "";
        for(int j = 0; j < lRow.size(); j++) {
            QString lData = lRow.at(j);
            if(j != 0) {lLine += " | ";}
            lLine += lData;
        }
        textEdit->append(lLine);
    }
}
//===============================================
void GManager::setData(QComboBox* comboBox, const QVector<QString>& data) {
    for(int i = 0; i < data.size(); i++) {
        QString lData = data.at(i);
        comboBox->addItem(lData);
    }
}
//===============================================
void GManager::setData2(QTextEdit* textEdit, const QVector<QString>& data) {
    textEdit->clear();
    for(int i = 0; i < data.size(); i++) {
        QString lData = data.at(i);
        textEdit->append(lData.toUpper());
    }
}
//===============================================
void GManager::setData2(QComboBox* comboBox, const QVector<QString>& data) {
    for(int i = 0; i < data.size(); i++) {
        QString lData = data.at(i);
        comboBox->addItem(lData.toUpper());
    }
}
//===============================================
// user
//===============================================
int GManager::countUser(const QString& username) {
    int lCount = GSQLite::Instance()->readData(QString(""
            "select count(*) from user_data\n"
            "where _username = '%1'\n"
            "").arg(username)).toInt();
    return lCount;
}
//===============================================
int GManager::countUser(const QString& username, const QString& password) {
    QString lPassword = getPassword(username, password);
    int lCount = GSQLite::Instance()->readData(QString(""
            "select count(*) from user_data\n"
            "where _username = '%1'\n"
            "and _password = '%2'\n"
            "").arg(username, lPassword)).toInt();
    return lCount;
}
//===============================================
QString GManager::getUserId(const QString& username) {
	QString lId = GSQLite::Instance()->readData(QString(""
            "select _id from user_data\n"
            "where _username = '%1'\n"
            "").arg(username));
    return lId;
}
//===============================================
void GManager::saveUser(const QString& username, const QString& password) {
    int lCount = countUser(username);
    if(lCount == 0) {
        insertUser(username, password);
    }
    else {
        updateUser(username, password);
    }
}
//===============================================
void GManager::insertUser(const QString& username, const QString& password) {
    QString lPassword = getPassword(username, password);
    GSQLite::Instance()->writeData(QString(""
            "insert into user_data (_username, _password)\n"
            "values ('%1', '%2')\n"
            "").arg(username).arg(lPassword));
}
//===============================================
void GManager::updateUser(const QString& username, const QString& password) {
    QString lPassword = getPassword(username, password);
    GSQLite::Instance()->writeData(QString(""
            "update user_data\n"
            "set _password = '%2',\n"
            "_date_update = current_timestamp\n"
            "where _username = '%1'\n"
            "").arg(username, lPassword));
}
//===============================================
QString GManager::getPassword(const QString& username, const QString& password) {
    QString lData = getMd5(QString("%1|%2").arg(username, password));
    return lData;
}
//===============================================
// login
//===============================================
void GManager::saveLogin(const QString& username, const QString& login) {
    int lCount = countLogin(username);
    if(lCount == 0) {
        insertLogin(username, login);
    }
    else {
        updateLogin(username, login);
    }
}
//===============================================
int GManager::countLogin() {
    int lCount = GSQLite::Instance()->readData(QString(""
            "select count(*) from login_data\n"
            "where _login = '1'\n"
            "")).toInt();
    return lCount;
}
//===============================================
int GManager::countLogin(QString username) {
    int lCount = GSQLite::Instance()->readData(QString(""
            "select count(*)\n"
            "from login_data t1, user_data t2\n"
            "where t1._user_id = t2._id\n"
            "and t2._username = '%1'\n"
            "").arg(username)).toInt();
    return lCount;
}
//===============================================
void GManager::insertLogin(QString username, QString login) {
    GSQLite::Instance()->writeData(QString(""
            "insert into login_data (_user_id, _login)\n"
            "select t2._id, '%2'\n"
            "from user_data t2\n"
            "where t2._username = '%1'\n"
            "").arg(username).arg(login));
}
//===============================================
void GManager::updateLogin(QString username, QString login) {
    GSQLite::Instance()->writeData(QString(""
            "update login_data\n"
            "set _login = '%2',\n"
            "_date_update = current_timestamp\n"
            "from login_data t1, user_data t2\n"
            "where t1._user_id = t2._id\n"
            "and t2._username = '%1'\n"
            "").arg(username).arg(login));
}
//===============================================
void GManager::updateLogin() {
    sGApp* lApp = GManager::Instance()->getData()->app;
    bool lLoginOn = (countLogin() != 0);
    lApp->login_connect->setEnabled(!lLoginOn);
    lApp->login_disconnect->setEnabled(lLoginOn);
}
//===============================================
void GManager::logOut() {
    GSQLite::Instance()->writeData(QString(""
            "update login_data\n"
            "set _login = '0',\n"
            "_date_update = current_timestamp\n"
            "where _login = '1'\n"
            ""));
}
//===============================================
// file_id
//===============================================
int GManager::countFileId(const QString& fileId) {
    int lCount = GSQLite::Instance()->readData(QString(""
            "select count(*) from file_id_data\n"
            "where _file_id = %1"
            "").arg(fileId)).toInt();
    return lCount;
}
//===============================================
void GManager::insertFileId(const QString& fileId) {
    GSQLite::Instance()->writeData(QString(""
            "insert into file_id_data (_file_id)\n"
            "values (%1)\n"
            "").arg(fileId));
}
//===============================================
// sqlite
//===============================================
QVector<QString> GManager::getTables() {
    QVector<QString> lTables = GSQLite::Instance()->readCol(QString(""
            "select name from sqlite_master\n"
            "where type = 'table'\n"
            "order by name\n"
            ""));
    return lTables;
}
//===============================================
QVector<QVector<QString>> GManager::getData(const QString& table) {
	QString lOrder = getFields(table).at(0);
    QVector<QVector<QString>> lData = GSQLite::Instance()->readMap(QString(""
            "select * from %1\n"
            "order by %2"
            "").arg(table).arg(lOrder));
    return lData;
}
//===============================================
QString GManager::getSchema(const QString& table) {
    QString lSchema = GSQLite::Instance()->readData(QString(""
            "select sql from sqlite_master\n"
            "where type = 'table'\n"
            "and name = '%1'\n"
            "").arg(table));
    return lSchema;
}
//===============================================
void GManager::deleteTable(const QString& table) {
    GSQLite::Instance()->writeData(QString(""
            "drop table %1\n"
            "").arg(table));
}
//===============================================
QStringList GManager::getFields(const QString& table) {
    return GSQLite::Instance()->getFields(table);
}
//===============================================
// file
//===============================================
QStringList GManager::getDirFiles(const QString& path, const QStringList& filters) {
    QDirIterator lDirIt(path, filters, QDir::Files, QDirIterator::NoIteratorFlags);
    QStringList lFiles;
    while (lDirIt.hasNext()) {
        lFiles << lDirIt.next();
    }
    return lFiles;
}
//===============================================
QString GManager::readFile(const QString& path) {
    QFile lFile(path);
    QString lData = "";
    if (lFile.open(QIODevice::ReadOnly)) {
        lData = lFile.readAll();
    }
    return lData;
}
//===============================================
// message
//===============================================
void GManager::showMessage(QWidget* parent, const QString& title, const QString& text) {
    QMessageBox::information(parent, title, text);
}
//===============================================
void GManager::showWarning(QWidget* parent, const QString& title, const QString& text) {
    QMessageBox::warning(parent, title, text);
}
//===============================================
void GManager::showError(QWidget* parent, const QString& title, const QString& text) {
    QMessageBox::critical(parent, title, text);
}
//===============================================
int GManager::showQuestion(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons) {
    return QMessageBox::question(parent, title, text, buttons);
}
//===============================================
int GManager::confirm(QWidget* parent) {
    int lOk = showQuestion(parent, "ReadyApp | Confirmation",
            "Êtes-vous sûr de bien vouloir continuer ?");
    return lOk;
}
//===============================================
// divers
//===============================================
QString GManager::getMd5(const QString& data) {
    QString lData = QString(QCryptographicHash::hash(data.toLatin1(), QCryptographicHash::Md5).toHex());
    return lData;
}
//===============================================
bool GManager::runCmd(const QString& cmd) {
    int lAnswer = system(cmd.toStdString().c_str());
    bool lOk = (lAnswer == 0);
    return lOk;
}
//===============================================
bool GManager::runCmd(const QString& cmd, QString& output) {
    QProcess lProcess;
    lProcess.start(cmd);
    lProcess.waitForFinished(-1);
    if(output != "") {output = lProcess.readAllStandardOutput();}
    bool lOk = (lProcess.error() == QProcess::UnknownError);
    return lOk;
}
//===============================================
bool GManager::runCmd2(const QString& cmd) {
    int lAnswer = system(cmd.toStdString().c_str());
    bool lOk = (lAnswer == 0);
    return lOk;
}
//===============================================
