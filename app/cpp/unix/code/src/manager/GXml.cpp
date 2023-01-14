//===============================================
#include "GXml.h"
//===============================================
GXml::GXml() {
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    m_node = 0;
    m_next = 0;
    xmlKeepBlanksDefault(0);
}
//===============================================
GXml::~GXml() {
    release();
}
//===============================================
void GXml::release() {
    if(m_xpathObj) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0;}
    if(m_xpath) {xmlXPathFreeContext(m_xpath); m_xpath = 0;}
    if(m_doc) {xmlFreeDoc(m_doc); m_doc = 0;}
}
//===============================================
void GXml::initModule() {
    xmlInitParser();
}
//===============================================
void GXml::cleanModule() {
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
bool GXml::loadXml(const GString& _xml) {
    GString lXml = _xml.trim();
    if(lXml == "") return false;
    m_doc = xmlParseDoc(BAD_CAST(lXml.c_str()));
    if(!m_doc) {
        m_logs.addError("Erreur le document n'a pas été initialisé.");
        return false;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {
        m_logs.addError("Erreur le xpath n'a pas été initialisé.");
        return false;
    }
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        m_logs.addError("Erreur le noeud racine n'a pas été initialisé.");
        return false;
    }
    return true;
}
//===============================================
bool GXml::loadFile(const GString& _filename) {
    if(_filename == "") return false;
    m_doc = xmlParseFile(_filename.c_str());
    if(!m_doc) {
        m_logs.addError("Erreur le document n'a pas été initialisé.");
        return false;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {
        m_logs.addError("Erreur le xpath n'a pas été initialisé.");
        return false;
    }
    m_node = xmlDocGetRootElement(m_doc);
    if(!m_node) {
        m_logs.addError("Erreur le noeud racine n'a pas été initialisé.");
        return false;
    }
    return true;
}
//===============================================
bool GXml::loadNode(const GString& _data) {
    if(_data.trim().isEmpty()) return false;
    if(!m_doc) return false;
    if(!m_node) return false;
    xmlNodePtr lNewNode;
    xmlParseInNodeContext(m_node, _data.c_str(), _data.size(), 0, &lNewNode);
    xmlNodePtr lNode = lNewNode->children;
    while(lNode) {
        xmlAddChild(m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNewNode);
    return true;
}
//===============================================
bool GXml::createDoc() {
    m_doc = xmlNewDoc(BAD_CAST "1.0");
    if(!m_doc) {
        m_logs.addError("Erreur le document n'a pas été initialisé.");
        return false;
    }
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {
        m_logs.addError("Erreur le xpath n'a pas été initialisé.");
        return false;
    }
    return true;
}
//===============================================
bool GXml::createNode(const GString& _name) {
    if(!m_node) {
        createDoc();
        m_node = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
        if(!m_node) {
            m_logs.addError("Erreur le noeud racine n'a pas été initialisé.");
            return false;
        }
        xmlDocSetRootElement(m_doc, m_node);
    }
    else {
        m_next = xmlNewNode(NULL, BAD_CAST(_name.c_str()));
        if(!m_next) {
            m_logs.addError("Erreur le noeud n'a pas été initialisé.");
            return false;
        }
        xmlAddChild(m_node, m_next);
    }
    return true;
}
//===============================================
bool GXml::createVNode(const GString& _name, const GString& _value, bool _isCData) {
    pushNode();
    createNode(_name);
    next();
    setValue(_value, _isCData);
    popNode();
    return true;
}
//===============================================
bool GXml::createXNode(const GString& _path) {
    int lCount = _path.countSep("/");
    GString lFirst = _path[0];
    GString lPath = "";
    if(lFirst == "/") lPath = "/";
    for(int i = 0, j = 0; i < lCount; i++) {
        GString lItem = _path.extract(i, "/");
        if(lItem == "") continue;
        if(j++ != 0) lPath += "/";
        lPath += lItem;
        if(!getXNode(lPath)) {
            createNode(lItem);
            next();
        }
    }
    return true;
}
//===============================================
bool GXml::next() {
    if(!m_next) return false;
    m_node = m_next;
    return true;
}
//===============================================
void GXml::pushNode() {
    if(!m_node) return;
    m_stack.push(m_node);
}
//===============================================
void GXml::popNode() {
    if(m_stack.empty()) return;
    m_node = m_stack.top();
    m_stack.pop();
}
//===============================================
bool GXml::getXNode(const GString& _path) {
    if(!m_doc) return false;
    if(!m_xpath) return false;
    m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), m_xpath);
    if(!m_xpathObj) return false;
    if(!m_xpathObj->nodesetval) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0; return false;}
    if(!m_xpathObj->nodesetval->nodeNr) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0; return false;}
    m_node = m_xpathObj->nodesetval->nodeTab[0];
    xmlXPathFreeObject(m_xpathObj);
    m_xpathObj = 0;
    return true;
}
//===============================================
GString GXml::getValue() const {
    if(!m_node) return "";
    GString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
bool GXml::setValue(const GString& _value, bool _isCData) {
    if(!m_doc) return false;
    if(!m_node) return false;
    if(!_isCData) {
        xmlNodeSetContent(m_node, BAD_CAST(_value.c_str()));
    }
    else {
        xmlNodePtr lNode = xmlNewCDataBlock(m_doc, BAD_CAST(_value.c_str()), _value.size());
        if(!lNode) {
            m_logs.addError("Erreur le noeud n'a pas été initialisé.");
            return false;
        }
        xmlAddChild(m_node, lNode);
    }
    return true;
}
//===============================================
bool GXml::replaceNode(GXml& _dom) {
    xmlReplaceNode(m_node, _dom.m_node);
    return true;
}
//===============================================
int GXml::countNode(const GString& _path) {
    if(!m_xpath) return 0;
    m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), m_xpath);
    if(!m_xpathObj) return 0;
    if(!m_xpathObj->nodesetval) {xmlXPathFreeObject(m_xpathObj); m_xpathObj = 0; return 0;}
    int lCount = m_xpathObj->nodesetval->nodeNr;
    xmlXPathFreeObject(m_xpathObj);
    m_xpathObj = 0;
    return lCount;
}
//===============================================
GString GXml::toString() const {
    if(!m_doc) return "";
    if(!m_node) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, "UTF-8", 4);
    GString lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
GString GXml::toNode() const {
    if(!m_node) return "";
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc, m_node, 0, 1);
    GString lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
void GXml::print() const {
    printf("%s\n", toString().c_str());
}
//===============================================
const GLog& GXml::getLogs() const {
    return m_logs;
}
//===============================================
