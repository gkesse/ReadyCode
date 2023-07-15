//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMYSQL      GMySQL::Instance()
#define czton       GMYSQL->convertZeroToNull
//===============================================
class GMySQL : public GObject {
public:
    typedef std::vector<GString> GRows;
    typedef std::vector<GRows> GMaps;

public:
    GMySQL();
    ~GMySQL();
    static GMySQL* Instance();
    GString toDatabase() const;
    int getId() const;
    GString convertZeroToNull(int _data);
    int getColumnCount(std::shared_ptr<sql::ResultSet>& _resultSet) const;
    bool openDatabase(std::shared_ptr<sql::Connection>& _conn);
    bool execQuery(const GString& _sql);
    bool insertQuery(const GString& _sql);
    bool readQuery(const GString& _sql, std::shared_ptr<sql::ResultSet>& _resultSet);
    GString readData(const GString& _sql);
    GRows readCol(const GString& _sql);
    GRows readRow(const GString& _sql);
    GMaps readMap(const GString& _sql);

private:
    static GMySQL* m_instance;
    int m_id;
};
//==============================================
#endif
//==============================================
