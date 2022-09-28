//===============================================
#ifndef _GLocale_
#define _GLocale_
//===============================================
#include "GObject.h"
//===============================================
class GLocale : public GObject {
public:
    GLocale();
    ~GLocale();
    void deserialize(const QString& _data, const QString& _code = "locale");
    void deserializeDom(const QString& _code = "locale");
    void initLocale();

private:
    QString m_encoding;
};
//==============================================
#endif
//==============================================
