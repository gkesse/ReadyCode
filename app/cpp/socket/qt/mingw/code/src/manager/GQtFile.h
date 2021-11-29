//===============================================
#ifndef _GQtFile_
#define _GQtFile_
//===============================================
#include "GInclude.h"
//===============================================
class GQtFile {
public:
    GQtFile();
    ~GQtFile();
    bool openFileWR(const QString& _filename);
    bool openFileRD(const QString& _filename);
    GQtFile& getFileInfo(const QString& _filename);
    QString getFilename() const;
    QString getFullname() const;
    QString getBasename() const;
    QString getExtension() const;
    bool atEnd() const;
    GQtFile& writeData(const QString& _data);
    GQtFile& writeData(int _data);
    GQtFile& getData(QString& _data);
    GQtFile& getData(int& _data);

private:
    QSharedPointer<QFile> m_QFile;
    QSharedPointer<QDataStream> m_QDataStream;
    QSharedPointer<QFileInfo> m_QFileInfo;
    int m_version;
};
//==============================================
#endif
//==============================================
