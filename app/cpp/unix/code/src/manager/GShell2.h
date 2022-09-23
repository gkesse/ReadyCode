//===============================================
#ifndef _GShell2_
#define _GShell2_
//===============================================
#include "GObject2.h"
//===============================================
class GShell2 : public GObject2 {
public:
    GShell2();
    ~GShell2();
    GString2 getTmpDir() const;
    GString2 getTmpInFilename() const;
    GString2 getTmpOutFilename() const;
    void createDir(const GString2& _dir);
    void tailFile(const GString2& _file);
    void cleanDir(const GString2& _dir);
    void runCommand(const GString2& _command);
    GString2 runSystem(const GString2& _command);
    GString2 runSystem(const GString2& _command, const GString2& _tmpDir, const GString2& _tmpInFile, const GString2& _tmpOutFile);
};
//==============================================
#endif
//==============================================
