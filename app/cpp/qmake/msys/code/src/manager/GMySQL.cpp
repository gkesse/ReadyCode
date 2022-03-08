//===============================================
#include "GMySQL.h"
#include "GLog.h"
#include "GXml.h"
#include "GPath.h"
//===============================================
GMySQL* GMySQL::m_instance = 0;
//===============================================
GMySQL::GMySQL(QObject* _parent) : GObject(_parent) {
	createDoms();
	m_mysql = 0;
	m_res = 0;
	m_row = 0;

	bool lDebug = (getMysqlItem("debug") == "1");

	if(lDebug) {
		printf("=> %-20s : %s\n", "mysql client info", mysql_get_client_info());
		printf("=> %-20s : %lu\n", "mysql client version", mysql_get_client_version());
	}
}
//===============================================
GMySQL::~GMySQL() {

}
//===============================================
GMySQL* GMySQL::Instance() {
	if(m_instance == 0) {
		m_instance = new GMySQL;
	}
	return m_instance;
}
//===============================================
void GMySQL::createDoms() {
	m_dom.reset(new GXml);
	m_dom->loadXmlFile(GRES("xml", "pad.xml"));
	m_dom->createXPath();
}
//===============================================
QString GMySQL::getMysqlItem(const QString& _data) const {
	m_dom->queryXPath(QString("/rdv/datas/data[code='mysql']/%1").arg(_data));
	m_dom->getNodeXPath();
	QString lData = m_dom->getNodeValue();
	return lData;
}
//===============================================
void GMySQL::open() {
	m_mysql = mysql_init(NULL);
	if(!m_mysql) {
		GLOG->addError(QString("Erreur la methode (GMySQL::open) a echoue (1)\n"
				"- %1").arg(mysql_errno(m_mysql)));
		return;
	}

	const char* lHostname = getMysqlItem("hostname").toStdString().c_str();
	const char* lUsername = getMysqlItem("username").toStdString().c_str();
	const char* lPassword = getMysqlItem("password").toStdString().c_str();
	const char* lDatabase = getMysqlItem("database").toStdString().c_str();
	int lPort = getMysqlItem("port").toInt();

	MYSQL* lAnswer = mysql_real_connect(m_mysql, lHostname, lUsername, lPassword, lDatabase, lPort, 0, 0);

	if(!lAnswer) {
		GLOG->addError(QString("Erreur la methode (GMySQL::open) a echoue (2)\n"
				"- hostname.....: (%1)\n"
				"- username.....: (%2)\n"
				"- port.........: (%3)\n"
				"- database.....: (%4)\n"
				"- mysql errno..: (%5)\n"
				"- mysql error..: (%6)").arg(lHostname).arg(lUsername).arg(lPort).arg(lDatabase).arg(mysql_errno(m_mysql)).arg(mysql_error(m_mysql)));
		return;
	}

	bool lDebug = (getMysqlItem("debug") == "1");

	if(lDebug) {
		printf("=> %-20s : %s\n", "mysql server", mysql_get_server_info(m_mysql));
	}
}
//===============================================
void GMySQL::close() {
	mysql_close(m_mysql);
}
//===============================================
void GMySQL::execQuery(const QString& _sql) {
	open();
	if(GLOG->hasError()) return;
    mysql_query(m_mysql, _sql.toStdString().c_str());
}
//===============================================
void GMySQL::storeResult() {
    m_res = mysql_store_result(m_mysql);
}
//===============================================
bool GMySQL::fetchRow() {
    m_row = mysql_fetch_row(m_res);
    return (m_row != 0);
}
//===============================================
int GMySQL::numFields() const {
	int lCount = mysql_num_fields(m_res);
	return lCount;
}
//===============================================
QString GMySQL::getData(int _index) const {
    return m_row[_index];
}
//===============================================
QString GMySQL::readData(const QString& _sql) {
	QString lData = "";
	if(GLOG->hasError()) return lData;
	execQuery(_sql);
	if(GLOG->hasError()) return lData;
	storeResult();
    while(fetchRow()) {
        lData = getData(0);
        break;
    }
	close();
	return lData;
}
//===============================================
QVector<QString> GMySQL::readCol(const QString& _sql) {
	QVector<QString> lDataMap;
	if(GLOG->hasError()) return lDataMap;
	execQuery(_sql);
	if(GLOG->hasError()) return lDataMap;
	storeResult();
    while(fetchRow()) {
        QString lData = getData(0);
        lDataMap.push_back(lData);
    }
	close();
	return lDataMap;
}
//===============================================
QVector<QString> GMySQL::readRow(const QString& _sql) {
	QVector<QString> lDataMap;
	if(GLOG->hasError()) return lDataMap;
	execQuery(_sql);
	if(GLOG->hasError()) return lDataMap;
	storeResult();
	int lFields = numFields();
    while(fetchRow()) {
    	for(int i = 0; i < lFields; i++) {
    		QString lData = getData(i);
            lDataMap.push_back(lData);
    	}
    	break;
    }
	close();
	return lDataMap;
}
//===============================================
QVector<QVector<QString>> GMySQL::readMap(const QString& _sql) {
	QVector<QVector<QString>> lDataMap;
	if(GLOG->hasError()) return lDataMap;
	execQuery(_sql);
	if(GLOG->hasError()) return lDataMap;
	storeResult();
	int lFields = numFields();
    while(fetchRow()) {
    	QVector<QString> lDataRow;
    	for(int i = 0; i < lFields; i++) {
    		QString lData = getData(i);
    		lDataRow.push_back(lData);
    	}
		lDataMap.push_back(lDataRow);
    }
	close();
	return lDataMap;
}
//===============================================
