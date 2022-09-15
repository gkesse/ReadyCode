//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GObject.h"
#include "GString2.h"
//===============================================
class GHttp;
//===============================================
class GSocket2 : public GObject {
public:
    GSocket2();
    ~GSocket2();
    //
    void setModule(const GString2& _module);
    void setHostname(const GString2& _hostname);
    void setMessage(const GString2& _message);
    void setNotFound(const GString2& _notFound);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setBacklog(int _backlog);
    //
    bool readMethod(int _socket, GString2& _data);
    bool readHeader(int _socket, GString2& _data);
    bool isHeader(char _char, int& _index) const;
    bool analyzeHeader(const GString2& _data, GHttp& _http);
    bool isLine(char _char, int& _index) const;
    //
    bool run();
    bool runGet(int _socket, GString2& _data);
    //
    static void* onThreadCB(void* _params);
    bool sendPageNotFound(int _socket);


private:
    static const int BUFFER_SIZE = 1024;
    static const int ANALYZE_SIZE = 10;
    static const int HEADER_SIZE = 1024;
    //
    GString2 m_module;
    GString2 m_hostname;
    GString2 m_message;
    GString2 m_notFound;
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    int m_backlog;
    //
    int m_socket;
    GSocket2* m_server;
};
//==============================================
#endif
//==============================================
