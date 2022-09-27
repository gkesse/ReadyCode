//===============================================
#ifndef _GShell2_
#define _GShell2_
//===============================================
#include "GObject2.h"
//===============================================
class GShell2 : public GObject2 {
    Q_OBJECT

public:
    GShell2(QObject* _parent = 0);
    ~GShell2();
    GString getTmpDir() const;
    GString getTmpInFilename() const;
    GString getTmpOutFilename() const;
    void createDir(const GString& _dir);
    void tailFile(const GString& _file);
    void cleanDir(const GString& _dir);
    void runCommand(const GString& _command);
    GString runSystem(const GString& _command);
    GString runSystem(const GString& _command, const GString& _tmpDir, const GString& _tmpInFile, const GString& _tmpOutFile);
};
//==============================================
#endif
//==============================================
