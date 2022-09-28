//===============================================
#ifndef _GShell_
#define _GShell_
//===============================================
#include "GObject.h"
//===============================================
class GShell : public GObject {
public:
    GShell();
    ~GShell();
    QString getTmpDir() const;
    QString getTmpInFilename() const;
    QString getTmpOutFilename() const;
    void createDir(const QString& _dir);
    void tailFile(const QString& _file);
    void cleanDir(const QString& _dir);
    void runCommand(const QString& _command);
    QString runSystem(const QString& _command);
    QString runSystem(const QString& _command, const QString& _tmpDir, const QString& _tmpInFile, const QString& _tmpOutFile);
};
//==============================================
#endif
//==============================================
