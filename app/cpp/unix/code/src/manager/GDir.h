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
    std::vector<std::string> openDir(const std::string& _path, bool _full = false) const;
};
//==============================================
#endif
//==============================================
