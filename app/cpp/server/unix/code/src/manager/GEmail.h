//===============================================
#ifndef _GEmail_
#define _GEmail_
//===============================================
#include "GManager.h"
//===============================================
class GEmail : public GManager {
public:
    class GAddr : public GObject {
    public:
        GAddr();
        ~GAddr();
        GAddr* clone();
        void setObj(const GAddr& _obj);
        void setAddr(const GString& _email, const GString& _name);
        void addAddr(const GString& _email, const GString& _name);
        GString serialize(const GString& _code = "email_addr") const;
        void deserialize(const GString& _data, const GString& _code = "email_addr");

    private:
        GString m_email;
        GString m_name;
    };

    class GAttach : public GObject {
    public:
        GAttach();
        ~GAttach();
        GAttach* clone();
        void setObj(const GAttach& _obj);
        void addFile(const GString& _file);
        GString serialize(const GString& _code = "email_attach") const;
        void deserialize(const GString& _data, const GString& _code = "email_attach");

    private:
        GString m_file;
    };

public:
    GEmail();
    ~GEmail();
    void setSubject(const GString& _subject);
    void setBody(const GString& _body);
    void setNoReply();
    GAddr& getTo();
    GAddr& getReply();
    GAddr& getCC();
    GAddr& getBCC();
    GAttach& getAttach();
    GString serialize(const GString& _code = "email") const;
    void deserialize(const GString& _data, const GString& _code = "email");
    void sendEmail();

private:
    GString m_body;
    GString m_subject;
    GAddr m_addrTo;
    GAddr m_addrReply;
    GAddr m_addrCC;
    GAddr m_addrBCC;
    GAttach m_attachFile;
};
//===============================================
#endif
//===============================================
