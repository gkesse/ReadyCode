//===============================================
#ifndef _GFormat_
#define _GFormat_
//===============================================
#include "GObject.h"
//===============================================
#define GFORMAT GFormat::Instance()
//===============================================
#define sformat(...) GFORMAT->getFormat(__VA_ARGS__)
//===============================================
class GFormat : public GObject {
public:
    GFormat();
    ~GFormat();
    static GFormat* Instance();
    std::string getFormat(const char* _format, ...);
    std::string getFormatInt(int _data, char* _buffer, int _size);

private:
    static GFormat* m_instance;
};
//==============================================
#endif
//==============================================
