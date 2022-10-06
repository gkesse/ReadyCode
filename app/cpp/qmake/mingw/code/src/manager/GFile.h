//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GManager.h"
//===============================================
class GFile : public GManager {
public:
    GFile();
    GFile(const GString& _fullname);
    ~GFile();

    GString serialize(const GString& _code = "file") const;
    bool deserialize(const GString& _data, const GString& _code = "file");

    void setId(int _id);
    void setFilename(const GString& _filename);
    void setContent(const GString& _content);
    GString getContent() const;

    void setFullname(const GString& _fullname);

    bool existFile() const;
    GString getContents() const;
    GString getContentBin() const;
    void setContents(const GString& _data);
    void setContentBin(const GString& _data);

    void saveFile();
    void downloadFile();

private:
    int m_id;
    GString m_filename;
    GString m_content;
    GString m_fullname;
};
//==============================================
#endif
//==============================================
