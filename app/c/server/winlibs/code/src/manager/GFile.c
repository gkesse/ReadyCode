//===============================================
#include "GFile.h"
//===============================================
static void GFile_delete(GFile* _this);
static GString* GFile_load(GFile* _this, const char* _filename);
static int GFile_size(GFile* _this, const char* _filename);
static int GFile_fsize(GFile* _this, FILE* _file);
//===============================================
GFile* GFile_new() {
    GFile* lObj = (GFile*)malloc(sizeof(GFile));
    lObj->m_parent = GObject_new();

    lObj->delete = GFile_delete;
    lObj->load = GFile_load;
    lObj->size = GFile_size;
    lObj->fsize = GFile_fsize;
    return lObj;
}
//===============================================
static void GFile_delete(GFile* _this) {
    assert(_this);
    _this->m_parent->delete(_this->m_parent);
    free(_this);
}
//===============================================
static GString* GFile_load(GFile* _this, const char* _filename) {
    assert(_this);
    FILE* lFile = fopen(_filename, "r");
    if(!lFile) return 0;
    int lSize = _this->fsize(_this, lFile);
    GString* lData = GString_new();
    lData->allocate(lData, lSize);
    fread(lData->m_data, 1, lSize, lFile);
    fclose(lFile);
    return lData;
}
//===============================================
static int GFile_size(GFile* _this, const char* _filename) {
    assert(_this);
    FILE* lFile = fopen(_filename, "r");
    if(!lFile) return 0;
    fseek(lFile, 0, SEEK_END);
    int lSize = ftell(lFile);
    fseek(lFile, 0, SEEK_SET);
    fclose(lFile);
    return lSize;
}
//===============================================
static int GFile_fsize(GFile* _this, FILE* _file) {
    assert(_this);
    fseek(_file, 0, SEEK_END);
    int lSize = ftell(_file);
    fseek(_file, 0, SEEK_SET);
    return lSize;
}
//===============================================
