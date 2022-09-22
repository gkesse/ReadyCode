//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
#define GSTRINGI GString::Instance()
//===============================================
#define sformat(...) GSTRINGI->getFormat(__VA_ARGS__)
//===============================================
class GString {
public:
    GString();
    GString(const QString& _data);
    GString(const std::string& _data);
    GString(const char* _data);
    GString(char _data);
    GString(int _data);
    GString(const GString& _data);
    ~GString();

    static GString* Instance();

    const char* c_str() const;
    const std::string& data() const;
    std::string& data();

    GString extract(int _pos, const GString& _sep) const;

    int count(const GString& _sep) const;

    bool isEmpty() const;
    bool isSep(char _char) const;

    int size() const;
    bool startBy(const GString& _data) const;
    int sepSize(int _pos, const GString& _sep) const;
    GString trim(const GString& _sep = " ") const;
    GString substr(int _pos, int _size = -1) const;

    int toInt() const;
    bool toInt(int& _data) const;

    GString getFormat(const char* _format, ...);

    GString& operator=(const GString& _data);
    GString& operator=(const QString& _data);
    GString& operator=(const std::string& _data);
    GString& operator=(const char* _data);
    GString& operator=(char _data);
    GString& operator=(int _data);

    GString& operator+=(const GString& _data);
    GString& operator+=(const QString& _data);
    GString& operator+=(const std::string& _data);
    GString& operator+=(const char* _data);
    GString& operator+=(char _data);
    GString& operator+=(int _data);

    bool operator==(const GString& _data) const;
    bool operator==(const QString& _data) const;
    bool operator==(const std::string& _data) const;
    bool operator==(const char* _data) const;
    bool operator==(char _data) const;
    bool operator==(int _data) const;

    bool operator!=(const GString& _data) const;
    bool operator!=(const QString& _data) const;
    bool operator!=(const std::string& _data) const;
    bool operator!=(const char* _data) const;
    bool operator!=(char _data) const;
    bool operator!=(int _data) const;

    char& operator[](int _index);
    const char& operator[](int _index) const;

    friend GString operator+(const GString& _data1, const GString& _data2);
    //
    friend std::ostream& operator<<(std::ostream& _os, const GString& _data);

private:
    static GString* m_instance;
    std::string m_data;
};
//==============================================
#endif
//==============================================
