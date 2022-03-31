//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GObject.h"
//===============================================
class GFile : public GObject {
    Q_OBJECT

public:
    GFile(QObject* _parent = 0);
    GFile(const QString& _filename);
    ~GFile();
    //
    QString getContent() const;

private:
    QString m_filename;
};
//==============================================
#endif
//==============================================
