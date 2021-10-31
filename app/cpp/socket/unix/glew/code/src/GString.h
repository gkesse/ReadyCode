//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
class GString {
public:
    GString();
    ~GString();
    void data(int _data);
    void data(const std::string& _data);
    void data(const char* _data);
    void data(const char* _data, int _size);
    std::string data() const ;
    void add(const char* _data);
    void add(const char* _data, int _size);
    void clear();
    int size() const;
    const char* c_str() const;
    void toChar(char* _buffer, int _size) const;
    int toChar(char* _buffer, int _index, int _size) const;
    void print() const;

public:
    friend std::ostream& operator<<(std::ostream& os, const GString& obj);

private:
    std::string m_data;
};
//==============================================
#endif
//==============================================
