//===============================================
#ifndef _GFile3_
#define _GFile3_
//===============================================
#include "GModule2.h"
//===============================================
class GFile3 : public GModule2 {
    Q_OBJECT

public:
    GFile3(QObject* _parent = 0);
    GFile3(const GString& _filename, QObject* _parent = 0);
    ~GFile3();

    GString serialize(const GString& _code = "file") const;
    bool deserialize(const GString& _data, const GString& _code = "file");

    void setKey(const GString& _key);
    void setFilename(const GString& _filename);
    void setContent(const GString& _content);
    void saveFile();

    bool existFile() const;
    GString getContents() const;
    void setContents(const GString& _data);

private:
    int m_id;
    GString m_key;
    GString m_filename;
    GString m_content;
};
//==============================================
#endif
//==============================================
