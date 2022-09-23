//===============================================
#ifndef _GString2_
#define _GString2_
//===============================================
#include "GInclude.h"
//===============================================
#define GSTRINGI GString2::Instance()
//===============================================
#define sformat(...) GSTRINGI->getFormat(__VA_ARGS__)
//===============================================
class GString2 {
public:
    GString2();
    GString2(const std::string& _data);
    GString2(const char* _data);
    GString2(char _data);
    GString2(bool _data);
    GString2(int _data);
    GString2(const GString2& _data);
    ~GString2();

    static GString2* Instance();

    const char* c_str() const;
    const std::string& data() const;
    std::string& data();

    std::string getFormat(const char* _format, ...);

    GString2 extract(int _pos, const GString2& _sep) const;
    int count(const GString2& _sep) const;
    bool isEmpty() const;
    bool isSep(char _char) const;
    int size() const;
    bool startBy(const GString2& _data) const;
    int sepSize(int _pos, const GString2& _sep) const;
    GString2 trim(const GString2& _sep = " ") const;
    GString2 substr(int _pos = 0, int _size = -1) const;

    bool toBool() const;
    char toChar() const;
    int toInt() const;
    bool toInt(int& _data, int _defaultValue = 0) const;

    void print() const;

    GString2& operator=(const GString2& _data);
    GString2& operator=(const std::string& _data);
    GString2& operator=(const char* _data);
    GString2& operator=(char _data);
    GString2& operator=(bool _data);
    GString2& operator=(int _data);
    //
    GString2& operator+=(const GString2& _data);
    GString2& operator+=(const std::string& _data);
    GString2& operator+=(const char* _data);
    GString2& operator+=(char _data);
    GString2& operator+=(int _data);
    //
    bool operator==(const GString2& _data) const;
    bool operator==(const std::string& _data) const;
    bool operator==(const char* _data) const;
    bool operator==(char _data) const;
    bool operator==(int _data) const;
    //
    bool operator!=(const GString2& _data) const;
    bool operator!=(const std::string& _data) const;
    bool operator!=(const char* _data) const;
    bool operator!=(char _data) const;
    bool operator!=(int _data) const;
    //
    char& operator[](int _index);
    const char& operator[](int _index) const;
    //
    friend GString2 operator+(const GString2& _data1, const GString2& _data2);
    //
    friend std::ostream& operator<<(std::ostream& _os, const GString2& _data);

private:
    static GString2* m_instance;
    std::string m_data;
};
//==============================================
#endif
//==============================================
