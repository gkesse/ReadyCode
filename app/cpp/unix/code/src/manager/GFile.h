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

    GString serialize() const;
    bool deserialize(const GString& _data);

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

    bool onModule();
    bool onSaveFile();
    bool saveFile();
    bool initFile();
    bool insertFile();
    bool updateFile();
    bool saveContent();
    bool downloadFile();

private:
    int m_id;
    GString m_homePath;
    GString m_filePath;
    GString m_fullname;
    GString m_filename;
    GString m_content;
};
//==============================================
#endif
//==============================================
