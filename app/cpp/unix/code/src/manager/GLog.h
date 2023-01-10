//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GInclude.h"
//===============================================
class GLog {
public:
    GLog();
    ~GLog();
    GString serialize(const GString& _code = "logs");
    void deserialize(const GString& _data, const GString& _code = "logs");
    GLog* clone();
    void clearMap();
    void setLog(const GLog& _log);
    void addError(const GString& _msg);
    void addLog(const GString& _msg);
    void addData(const GString& _msg);
    void addLogs(const GLog& _obj);
    bool hasErrors() const;
    void showErrors();

private:
    GString m_type;
    GString m_side;
    GString m_msg;
    std::vector<GLog*> m_map;
};
//==============================================
#endif
//==============================================
