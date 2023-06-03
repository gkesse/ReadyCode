//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GFile GFile;
//===============================================
struct _GFile {
    GObject* m_parent;

    void (*delete)(GFile* _this);
    GString* (*load)(GFile* _this, const char* _filename);
    int (*size)(GFile* _this, const char* _filename);
    int (*fsize)(GFile* _this, FILE* _pFile);
};
//===============================================
GFile* GFile_new();
//===============================================
#endif
//===============================================
