//===============================================
#ifndef _GDir_
#define _GDir_
//===============================================
#include "GObject.h"
//===============================================
class GDir : public GObject {
public:
    GDir();
    ~GDir();
    std::vector<GString> openDir(const GString& _path, bool _fullOn, bool _dotOn) const;
};
//==============================================
#endif
//==============================================
