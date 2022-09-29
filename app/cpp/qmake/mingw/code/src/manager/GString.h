//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
#define GSTRINGI        GString::Instance()
#define GFORMAT(...)    GSTRINGI->getFormat(__VA_ARGS__)
//===============================================
class GString {
public:
    GString();
    GString(const QString& _data);
    GString(const std::string& _data);
    GString(const char* _data);
    GString(char _data);
    GString(bool _data);
    GString(int _data);
    GString(const std::vector<char>& _data);
    GString(const std::vector<uchar>& _data);
    GString(const GString& _data);
    ~GString();

    static GString* Instance();

    void clear();
    bool allocate(int _size);
    void create(const QString& _data);
    void create(const std::string& _data);
    void create(const char* _data);
    void create(char _data);
    void create(bool _data);
    void create(int _data);
    void create(const std::vector<char>& _data);
    void create(const std::vector<uchar>& _data);
    void create(const GString& _data);

    char*& data();
    const char* data() const;
    const char* c_str() const;

    GString extract(int _pos, const GString& _sep) const;

    int countSep(const GString& _sep) const;

    bool isEmpty() const;
    bool isSep(char _char) const;

    int size() const;
    bool startBy(const GString& _data) const;
    int sepSize(int _pos, const GString& _sep) const;
    GString trim(const GString& _sep = " ") const;
    GString substr(int _pos, int _size = -1) const;

    bool toBool() const;
    int toInt() const;
    bool toInt(int& _data, int _defaultValue = 0) const;
    std::vector<char> toVector() const;

    GString getFormat(const char* _format, ...) const;
    GString getFilename() const;
    void print() const;

    GString& operator=(const GString& _data);
    GString& operator=(const QString& _data);
    GString& operator=(const std::vector<char>& _data);
    GString& operator=(const std::vector<uchar>& _data);
    GString& operator=(const std::string& _data);
    GString& operator=(const char* _data);
    GString& operator=(char _data);
    GString& operator=(bool _data);
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
    char* m_data;
    int m_size;
};
//==============================================
#endif
//==============================================
