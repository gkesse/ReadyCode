//===============================================
#ifndef _GError_
#define _GError_
//===============================================
#include "GObject.h"
//===============================================
class GError : public GObject {
public:
    GError();
    ~GError();
    GObject* clone();
    //
    std::string serialize(const std::string& _code = "errors");
    void deserialize(const std::string& _data, const std::string& _code = "errors");
    std::string deserializer(const std::string& _code = "errors") const;
    //
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _error);
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, GError& _error);
    std::string toString() const;
    bool hasErrors() const;
    void clearErrors();
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _res);
    std::vector<std::string>& getErrors();

private:
    std::string m_side;
    std::string m_msg;
    std::vector<std::string> m_errors;
};
//==============================================
#endif
//==============================================
