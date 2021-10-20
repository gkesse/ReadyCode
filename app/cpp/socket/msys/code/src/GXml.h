//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GInclude.h"
//===============================================
class GXml {
public:
    GXml();
    ~GXml();
    void free();
    void filename(const std::string& filename);
    void blank();
    void parse();
    void root();
    void node(const std::string& _node);
    void attribute(const std::string& _key, const std::string& _value);
    void data(const std::string& _data);
    void child(GXml& _child);
    void child(const std::string& _key, const std::string& _value);
    void nextSibling(GXml& _child);
    void prevSibling(GXml& _child);
    void append(GXml& _child);
    void xpath(GXml& _xml, const std::string& _xpath);
    void print() const;
    void print(GXml& _xml) const;
    void create(const std::string& _reference, const std::string& _name, const std::string& _price);
    
protected:
    std::string m_filename;
    xmlNodePtr m_node;
    xmlDocPtr m_doc;
};
//==============================================
#endif
//==============================================
