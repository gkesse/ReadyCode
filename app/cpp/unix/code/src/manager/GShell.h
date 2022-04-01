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
    std::string getTmpDir() const;
    std::string getTmpInFilename() const;
    std::string getTmpOutFilename() const;
    void createDir(const std::string& _dir);
    void cleanDir(const std::string& _dir);
    void runCommand(const std::string& _command);
    std::string runSystem(const std::string& _command);
    std::string runSystem(const std::string& _command, const std::string& _tmpDir, const std::string& _tmpInFile);
    std::string runSystem(const std::string& _command, const std::string& _tmpDir, const std::string& _tmpInFile, const std::string& _tmpOutFile);
};
//==============================================
#endif
//==============================================
