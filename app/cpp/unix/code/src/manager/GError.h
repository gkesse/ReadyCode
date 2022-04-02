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
    //
    void addError(const std::string& _error);
    std::string toString() const;
    bool hasErrors() const;
    void clearErrors();
    void loadErrors(const std::string& _res);
    std::vector<std::string>& getErrors();

private:
    std::vector<std::string> m_errors;
};
//==============================================
#endif
//==============================================
