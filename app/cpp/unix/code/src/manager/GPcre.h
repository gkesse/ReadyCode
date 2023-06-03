//===============================================
#ifndef _GPcre_
#define _GPcre_
//===============================================
#include "GObject.h"
//===============================================
class GPcre : public GObject {
public:
    GPcre();
    ~GPcre();
    GObject* clone() const;
    void setObj(const GObject& _obj);
    void setObj(const GPcre& _obj);
    void setDataIn(const GString& _dataIn);
    void setPattern(const GString& _pattern);
    GString serialize(const GString& _code = "pcre");
    void deserialize(const GString& _data, const GString& _code = "pcre");
    bool run();

private:
    static const int PCRE_BUFFER_SIZE = 30;

private:
    GString m_dataIn;
    GString m_pattern;

    GString m_dataOut;
};
//==============================================
#endif
//==============================================
