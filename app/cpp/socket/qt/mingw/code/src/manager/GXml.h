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
	void blank();
	void parse(const std::string& _filename);
	void doc(const std::string& _version = "1.0");
	void encoding(const std::string& _encoding);
	void root();
	void root(const std::string& _name);
	void node(const std::string& _node);
	void attribute(const std::string& _key, const std::string& _value);
	void attributes(const std::string& _key, const std::string& _value);
	void data(const std::string& _data);
	void child(GXml& _child);
	void child(const std::string& _key, const std::string& _value);
	void child(GXml& _child, const std::string& _key);
	void child(GXml& _child, const std::string& _key, const std::string& _value);
	void content(const std::string& _value);
	void nextSibling(GXml& _child);
	void prevSibling(GXml& _child);
	void append(GXml& _child);
	void xpath(GXml& _xml, const std::string& _xpath);
	void toString(GXml& _xml, std::string& _data);
	void print() const;
	void print(GXml& _xml) const;
	void create(const std::string& _reference, const std::string& _name, const std::string& _price);

protected:
	xmlNodePtr m_node;
	xmlDocPtr m_doc;
};
//==============================================
#endif
//==============================================
