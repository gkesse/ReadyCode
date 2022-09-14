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
    void setNotFound(const std::string& _notFound);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setBacklog(int _backlog);
    //
    bool analyzeMethod(int _socket, std::string& _data);
    bool analyzeHeader(int _socket, std::string& _data);
    bool compare(const std::string& _data1, const std::string& _data2, const std::string& _sep = " ");
    bool isHeader(int _char, int& _index) const;
    //
    bool sendPageNotFound(int _socket);
    //
    bool readData(int _socket, std::string& _data, int _max = 0);
    bool getMethod(const std::string& _data, std::string& _method);
    bool getUrl(const std::string& _data, std::string& _method);
    bool getProtocol(const std::string& _data, std::string& _protocol);
    //
    bool run();
    bool runGet(int _socket, std::string& _data);

private:
    static const int BUFFER_SIZE = 1024;
    static const int ANALYZE_SIZE = 10;
    static const int HEADER_SIZE = 1024;
    //
    std::string m_module;
    std::string m_hostname;
    std::string m_message;
    std::string m_notFound;
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
