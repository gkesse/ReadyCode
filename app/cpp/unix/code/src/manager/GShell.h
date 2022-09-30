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
