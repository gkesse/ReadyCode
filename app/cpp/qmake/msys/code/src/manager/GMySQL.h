//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMYSQL GMySQL::Instance()
//===============================================
class GMySQL : public GObject {
	Q_OBJECT

public:
	GMySQL(QObject* _parent = 0);
	~GMySQL();
	static GMySQL* Instance();
	void createDoms();
	QString getMysqlItem(const QString& _data) const;
	void open();
	void close();
	void execQuery(const QString& _sql);
	void storeResult();
	bool fetchRow();
	int numFields() const;
	QString getData(int _index) const;
	QString readData(const QString& _sql);
	QVector<QString> readCol(const QString& _sql);
	QVector<QString> readRow(const QString& _sql);
	QVector<QVector<QString>> readMap(const QString& _sql);

private:
	static GMySQL* m_instance;
	//
	MYSQL* m_mysql;
	MYSQL_RES* m_res;
	MYSQL_ROW m_row;
	//
	QString m_hostname;
	QString m_username;
	QString m_password;
	int m_port;
	QString m_charset;
};
//==============================================
#endif
//==============================================
