//===============================================
#include "GQtFile.h"
#include "GQt.h"
#include "GQtLog.h"
//===============================================
GQtFile::GQtFile() {
    m_version = QDataStream::Qt_4_3;
}
//===============================================
GQtFile::~GQtFile() {

}
//===============================================
bool GQtFile::openFileWR(const QString& _filename) {
    m_QFile.reset(new QFile(_filename));
    if(!m_QFile->open(QIODevice::WriteOnly)) {
        GQTLOG->addError(QString("Erreur l'ouverture du fichier a échoué : %)").arg(_filename));
        return false;
    }

    m_QDataStream.reset(new QDataStream(m_QFile.get()));
    m_QDataStream->setVersion(m_version);
    return true;
}
//===============================================
bool GQtFile::openFileRD(const QString& _filename) {
    m_QFile.reset(new QFile(_filename));
    if(!m_QFile->open(QIODevice::ReadOnly)) {
        GQTLOG->addError(QString("Erreur l'ouverture du fichier a échoué : %)").arg(_filename));
        return false;
    }

    m_QDataStream.reset(new QDataStream(m_QFile.get()));
    m_QDataStream->setVersion(m_version);
    return true;
}
//===============================================
GQtFile& GQtFile::getFileInfo(const QString& _filename) {
    m_QFileInfo.reset(new QFileInfo(_filename));
    return *this;
}
//===============================================
QString GQtFile::getFilename() const {
    return m_QFileInfo->fileName();
}
//===============================================
QString GQtFile::getFullname() const {
    return m_QFileInfo->absoluteFilePath();
}
//===============================================
QString GQtFile::getBasename() const {
    return m_QFileInfo->baseName();
}
//===============================================
QString GQtFile::getExtension() const {
    return m_QFileInfo->completeSuffix();
}
//===============================================
bool GQtFile::atEnd() const {
    return m_QDataStream->atEnd();
}
//===============================================
GQtFile& GQtFile::writeData(const QString& _data) {
    *m_QDataStream << _data;
    return *this;
}
//===============================================
GQtFile& GQtFile::writeData(int _data) {
    *m_QDataStream << _data;
    return *this;
}
//===============================================
GQtFile& GQtFile::getData(QString& _data) {
    *m_QDataStream >> _data;
    return *this;
}
//===============================================
GQtFile& GQtFile::getData(int& _data) {
    *m_QDataStream >> _data;
    return *this;
}
//===============================================
