//===============================================
#ifndef _GJson_
#define _GJson_
//===============================================
#include "GInclude.h"
//===============================================
class GJson {
public:
    GJson(bool _isFormat = true);
    ~GJson();
    void createObject();
    void createArray();
    void pushObject();
    void popObject();
    void initParent();
    void initChild();
    void addData(const GString& _key, const GString& _value);
    void addData(const GString& _value);
    void addObject();
    void addObject(const GString& _key);
    void clearJson();
    GString toString() const;

protected:
    json_object* m_current;
    std::stack<json_object*> m_map;
    json_object* m_parent;
    json_object* m_child;
    bool m_isFormat;
};
//==============================================
#endif
//==============================================
