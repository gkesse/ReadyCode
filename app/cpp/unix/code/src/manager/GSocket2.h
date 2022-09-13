//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GObject.h"
//===============================================
class GCode;
//===============================================
class GSocket2 : public GObject {
public:
    GSocket2();
    ~GSocket2();
    //
    void setModule(const std::string& _module);
    void setHostname(const std::string& _hostname);
    void setMessage(const std::string& _message);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setBacklog(int _backlog);
    //
    bool isEnd(int _char, int& _index) const;
    bool readData(int _socket, std::string& _data, int _max = 0);
    bool getMethod(const std::string& _data, std::string& _method);
    bool getUrl(const std::string& _data, std::string& _method);
    bool getVersion(const std::string& _data, std::string& _method);
    //
    bool run();
    bool runGet(int _socket, const std::string& _data);

private:
    static const int BUFFER_SIZE = 1024;
    std::string m_module;
    std::string m_hostname;
    std::string m_message;
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    int m_backlog;
};
//==============================================
#endif
//==============================================
