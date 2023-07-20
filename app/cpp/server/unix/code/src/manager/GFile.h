//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GManager.h"
//===============================================
class GFile : public GManager {
public:
    GFile();
    ~GFile();
    GString serialize(const GString& _code = "file") const;
    void deserialize(const GString& _data, const GString& _code = "file");
    void run(const GString& _data);
    void onSaveFile(const GString& _data);

private:
    int m_id;
    GString m_name;
    int m_size;
    GString m_mimeType;
    GString m_data;
    GDateTime m_createDate;
    GDateTime m_updateDate;
};
//==============================================
#endif
//==============================================
