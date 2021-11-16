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
    GXml& loadFile(const std::string& _filename);
    GXml& parseData(const std::string& _xml);
    GXml& createDoc();
    GXml& addVersion(const std::string& _version = "1.0");
    GXml& addEncoding(const std::string& _encoding = "UTF-8");
    GXml& addStandalone(const std::string& _standalone = "yes");
    GXml& addDocNode(GXml& _doc);
    GXml& docToString(std::string& _data);
    GXml& createRoot(const std::string& _name);
    GXml& getRoot();
    GXml& appendChild(GXml& _child, const std::string& _name);
    GXml& appendAttribute(const std::string& _name, const std::string& _value);
    GXml& setNodeValue(const std::string& _value);
    GXml& getNodeValue(std::string& _value);
    GXml& nodeIsNull(bool& _isNull);
    GXml& nodeToString(std::string& _data);
    GXml& firstChild(GXml& _child);
    GXml& lastChild(GXml& _child);
    GXml& nextSibling(GXml& _child);
    GXml& prevSibling(GXml& _child);
    GXml& attributeIsNull(bool& _isNull);
    GXml& firstAttribute(GXml& _child);
    GXml& lastAttribute(GXml& _child);
    GXml& nextAttribute(GXml& _child);
    GXml& prevAttribute(GXml& _child);
    GXml& saveFile(const std::string& _filename);
    GXml& printDoc();

protected:
    pugi::xml_document m_doc;
    pugi::xml_parse_result m_result;
    pugi::xml_node m_node;
    pugi::xml_attribute m_attribute;
};
//==============================================
#endif
//==============================================
