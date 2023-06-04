//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GLog {
public:
    GLog();
    ~GLog();
    void clear();
    void setObj(const GLog& _obj);
    void addError(const GString& _msg);
    void addLog(const GString& _msg);
    void addData(const GString& _msg);
    void addLogs(const GLog& _obj);
    bool hasErrors() const;
    bool hasLogs() const;
    bool hasDatas() const;
    void print() const;

private:
    GString m_type;
    GString m_side;
    GString m_msg;
    std::vector<GLog*> m_map;
};
//===============================================
#endif
//===============================================
