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
    std::string getTmpFile() const;
    std::string getLogFile(const std::string& _key, const std::string& _date, const std::string& _ext) const;
    void createDir(const std::string& _dir);
    void runSystem(const std::string& _command);
    void runSystem(const std::string& _command, const std::string& _tmpDir, const std::string& _tmpFile);
};
//==============================================
#endif
//==============================================
