//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
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

    const char* c_str() const;
    const QString& data() const;
    QString& data();
    GString extract(int _pos, const GString& _sep);
    int count(const GString& _sep);
    bool isEmpty() const;
    bool isSep(char _char) const;
    int size() const;
    bool startBy(const GString& _data) const;
    int sepSize(int _pos, const GString& _sep) const;
    GString trim(const GString& _sep = " ");
    int toInt() const;

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

    bool operator==(const GString& _data);
    bool operator==(const QString& _data);
    bool operator==(const std::string& _data);
    bool operator==(const char* _data);
    bool operator==(char _data);
    bool operator==(int _data);

    bool operator!=(const GString& _data);
    bool operator!=(const QString& _data);
    bool operator!=(const std::string& _data);
    bool operator!=(const char* _data);
    bool operator!=(char _data);
    bool operator!=(int _data);

    char& operator[](int _index);
    const char& operator[](int _index) const;

    friend GString operator+(const GString& _data1, const GString& _data2);
    //
    friend std::ostream& operator<<(std::ostream& _os, const GString& _data);

private:
    QString m_data;
};
//==============================================
#endif
//==============================================
