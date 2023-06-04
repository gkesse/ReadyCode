//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
class GString {
public:
    GString();
    GString(const char* _data, int _size);
    GString(const char* _data);
    GString(const std::string& _data);
    GString(const GString& _data);
    ~GString();
    void clear();
    void create(const char* _data, int _size);
    bool isEmpty() const;
    const char* c_str() const;
    void print() const;

    GString& operator=(const char* _data);
    GString& operator=(const std::string& _data);
    GString& operator=(const GString& _data);

    bool operator==(const char* _data) const;
    bool operator==(const std::string& _data) const;
    bool operator==(const GString& _data) const;

private:
    char* m_data;
    int m_size;
};
//===============================================
#endif
//===============================================
