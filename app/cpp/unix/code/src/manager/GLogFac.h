//===============================================
#ifndef _GLogFac_
#define _GLogFac_
//===============================================
#include "GManager.h"
//===============================================
class GLogFac : public GManager {
public:
    GLogFac();
    ~GLogFac();
    GString serialize(const GString& _code = "logs");
    void deserialize(const GString& _data, const GString& _code = "logs");
    bool onModule(const GString& _data);
    bool onCatLogFile();
    bool onTailLogFile();
    bool catLogFile();
    bool tailLogFile();

private:
    GString m_logFilename;
};
//==============================================
#endif
//==============================================
