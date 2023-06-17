//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
#define GSTRING     GString::Instance()
#define sformat     GSTRING->getFormat
//===============================================
class GString {
public:
    GString();
    GString(char* _data);
    GString(char* _data, int _size);
    GString(const char* _data);
    GString(const char* _data, int _size);
    GString(const std::string& _data);
    GString(const QString& _data);
    GString(const GString& _data);
    ~GString();
    static GString* Instance();
    void clear();
    void create(int _size);
    void create(const char* _data, int _size);
    bool isEmpty() const;
    const char* c_str() const;
    int size() const;
    GString getFormat(const char* _format, ...) const;
    std::vector<GString> split(const GString& _sep) const;
    GString toUtf8() const;
    GString toBase64() const;
    GString fromBase64() const;
    void print() const;

    GString& operator=(char* _data);
    GString& operator=(const char* _data);
    GString& operator=(const std::string& _data);
    GString& operator=(const QString& _data);
    GString& operator=(const GString& _data);

    bool operator==(const char* _data) const;
    bool operator==(const std::string& _data) const;
    bool operator==(const GString& _data) const;

    bool operator!=(const char* _data) const;
    bool operator!=(const std::string& _data) const;
    bool operator!=(const GString& _data) const;

    bool operator<(const GString& _data) const;

    GString& operator+=(const char* _data);
    GString& operator+=(const std::string& _data);
    GString& operator+=(const GString& _data);

    char& operator[](int i);
    const char& operator[](int i) const;

private:
    static GString* m_instance;
    char* m_data;
    int m_size;
};
//===============================================
#endif
//===============================================
