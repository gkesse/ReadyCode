//===============================================
#ifndef _GString2_
#define _GString2_
//===============================================
#include "GObject.h"
//===============================================
class GString2 : public GObject {
public:
    GString2();
    GString2(const std::string& _data);
    GString2(const char* _data);
    GString2(char _data);
    GString2(int _data);
    GString2(const GString2& _data);
    ~GString2();

    const char* c_str() const;
    const std::string& data() const;
    std::string& data();
    GString2 extract(int _pos, const GString2& _sep);
    bool isEmpty() const;
    bool isSep(char _char) const;
    int size() const;
    bool startBy(const GString2& _data) const;
    GString2 trim(const GString2& _sep = " ");
    int toInt() const;

    GString2& operator=(const GString2& _data);
    GString2& operator=(const std::string& _data);
    GString2& operator=(const char* _data);
    GString2& operator=(char _data);
    GString2& operator=(int _data);
    //
    GString2& operator+=(const GString2& _data);
    GString2& operator+=(const std::string& _data);
    GString2& operator+=(const char* _data);
    GString2& operator+=(char _data);
    GString2& operator+=(int _data);
    //
    bool operator==(const GString2& _data);
    bool operator==(const std::string& _data);
    bool operator==(const char* _data);
    bool operator==(char _data);
    bool operator==(int _data);
    //
    bool operator!=(const GString2& _data);
    bool operator!=(const std::string& _data);
    bool operator!=(const char* _data);
    bool operator!=(char _data);
    bool operator!=(int _data);
    //
    char& operator[](int _index);
    const char& operator[](int _index) const;
    //
    friend GString2 operator+(const GString2& _data1, const GString2& _data2);
    //
    friend std::ostream& operator<<(std::ostream& _os, const GString2& _data);

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
