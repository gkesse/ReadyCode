//===============================================
#ifndef _GFormat_
#define _GFormat_
//===============================================
#include "GObject.h"
//===============================================
#define GFORMAT GFormat::Instance()
//===============================================
class GFormat : public GObject {
public:
    GFormat();
    ~GFormat();
    static GFormat* Instance();
    std::string sformat(const char* _format, ...);

private:
    static GFormat* m_instance;
    //
    static const int BUFFER_SIZE = 1024;
    //
    char m_buffer[BUFFER_SIZE + 1];
};
//==============================================
#endif
//==============================================
