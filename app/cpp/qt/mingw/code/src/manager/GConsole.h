//===============================================
#ifndef _GConsole_
#define _GConsole_
//===============================================
#include "GObject.h"
//===============================================
#define GCONSOLE GConsole::Instance()
//===============================================
class GConsole : public GObject {
public:
    GConsole();
    ~GConsole();
    static GConsole* Instance();
    //
    void runConsole();
    GConsole* getConsole() const;
    std::queue<std::string>& getDataIn();
    bool& getReadyOn();
    void stopConsole();
    void setPseudo(const std::string& _pseudo);
    std::string getPseudo() const;
    void setPseudoId(const std::string& _pseudoId);
    std::string getPseudoId() const;
    //
    static DWORD WINAPI onRunConsole(LPVOID _params);

private:
    static GConsole* m_instance;
    //
    bool m_consoleOn;
    GConsole* m_console;
    std::queue<std::string> m_dataIn;
    bool m_readyOn;
    std::string m_pseudo;
    std::string m_pseudoId;
};
//==============================================
#endif
//==============================================
