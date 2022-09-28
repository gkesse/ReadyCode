//===============================================
#include "GXml.h"
#include "GLog.h"
//===============================================
GXml::GXml()
: GObject() {
    m_node = 0;
    m_queryNode = 0;
    m_doc = 0;
    m_xpath = 0;
    m_xpathObj = 0;
    m_filename = "";
    xmlKeepBlanksDefault(0);
}
//===============================================
GXml::~GXml() {
    xmlXPathFreeObject(m_xpathObj);
    xmlXPathFreeContext(m_xpath);
    xmlFreeDoc(m_doc);
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
bool GXml::loadXml(const QString& _data) {
    QString lData = _data.trimmed();
    if(lData == "") return false;
    m_doc = xmlParseDoc(BAD_CAST(lData.toStdString().c_str()));
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::loadFile(const QString& _filename) {
    if(_filename == "") return false;
    m_doc = xmlParseFile(_filename.toStdString().c_str());
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_filename = _filename;
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::loadNode(const QString& _data, const QString& _encoding) {
    if(!m_node) return false;
    xmlNodePtr lNewNode;
    QString lData = _data;
    lData = "<rdv>" + _data + "</rdv>";
    xmlChar* lDataOut = convertData(lData.toStdString().c_str(), _encoding.toStdString().c_str());
    int lSizeOut = xmlStrlen(lDataOut);
    GLOGT(eGOFF, lData);
    xmlParserErrors lError = xmlParseInNodeContext(m_node, (char*)lDataOut, lSizeOut, 0, &lNewNode);
    GLOGT(eGOFF, QString("%1").arg(lError));
    if(!lNewNode) {GERROR_ADD(eGERR, "Erreur lors du chargement du noeud."); return false;}
    xmlNodePtr lNode = lNewNode->children;
    while(lNode) {
        xmlAddChild(m_node, xmlCopyNode(lNode, 1));
        lNode = lNode->next;
    }
    xmlFreeNode(lNewNode);
    return true;
}
//===============================================
bool GXml::saveXml(const QString& _filename, const QString& _encoding, int _format) {
    QString lFilename = "";
    if(_filename != "") {
        lFilename = _filename;
    }
    else {
        lFilename = m_filename;
    }
    if(lFilename == "") {GERROR_ADD(eGERR, "Erreur le nom du fichier est vide."); return false;}
    xmlSaveFormatFileEnc(lFilename.toStdString().c_str(), m_doc, _encoding.toStdString().c_str(), _format);
    return true;
}
//===============================================
bool GXml::isValidXml() const {
    if(!m_doc) return false;
    return true;
}
//===============================================
QString GXml::getNodeValue() const {
    if(!countXPath()) return "";
    QString lData = (char*)xmlNodeGetContent(m_node);
    return lData;
}
//===============================================
bool GXml::createXNode(const QString& _path, const QString& _value, bool _isCData) {
    QString lPath = _path.trimmed();
    if(lPath == "") return false;
    QChar lChar = lPath[0];
    bool lRootOn = (lChar == '/');
    QStringList lMap = lPath.split('/');
    lPath = "";

    m_queryNode = m_node;

    for(int i = 0; i < (int)lMap.size(); i++) {
        QString lItem = lMap[i];
        lItem = lItem.trimmed();
        if(lItem == "") continue;
        if(lPath != "" || lRootOn) lPath += "/";
        lPath += lItem;
        getXPath(lPath, lRootOn);
        if(countXPath() == 0) {
            createNode(lItem);
        }
    }
    if(_value != "") {
        setNodeValue(_value, _isCData);
    }
    m_queryNode = 0;
    return true;
}
//===============================================
bool GXml::createDoc(const QString& _version) {
    m_doc = xmlNewDoc(BAD_CAST(_version.toStdString().c_str()));
    if(!m_doc) {GERROR_ADD(eGERR, "Erreur lors de la création du document."); return false;}
    m_xpath = xmlXPathNewContext(m_doc);
    if(!m_xpath) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::createNode(const QString& _nodename) {
    if(!m_doc) return false;
    xmlNodePtr lNode = xmlNewNode(NULL, BAD_CAST(_nodename.toStdString().c_str()));
    if(!lNode) GERROR_ADD(eGERR, "Erreur lors de la création du noeud.");
    if(!m_node) {
        xmlDocSetRootElement(m_doc, lNode);
    }
    else {
        xmlAddChild(m_node, lNode);
    }
    m_node = lNode;
    return true;
}
//===============================================
bool GXml::setNodeValue(const QString& _value, bool _isCData) {
    if(!m_doc) return false;
    if(!m_node) return false;
    if(!_isCData) {
        xmlNodeSetContent(m_node, BAD_CAST(_value.toStdString().c_str()));
    }
    else {
        xmlNodePtr lNode = xmlNewCDataBlock(m_doc, BAD_CAST(_value.toStdString().c_str()), _value.size());
        if(!lNode) GERROR_ADD(eGERR, "Erreur lors de la création du noeud.");
        xmlAddChild(m_node, lNode);
    }
    return true;
}
//===============================================
bool GXml::queryXPath(const QString& _path, bool _isRoot) {
    if(!m_xpath) return false;
    if(_isRoot) {
        m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.toStdString().c_str()), m_xpath);
    }
    else {
        if(m_queryNode) {
            m_xpathObj = xmlXPathNodeEval(m_queryNode, BAD_CAST(_path.toStdString().c_str()), m_xpath);
        }
        else {
            m_xpathObj = xmlXPathEvalExpression(BAD_CAST(_path.toStdString().c_str()), m_xpath);
        }
    }
    if(!m_xpathObj) {GERROR_ADD(eGERR, "Erreur lors de la création du xpath."); return false;}
    return true;
}
//===============================================
bool GXml::getXPath(const QString& _path, bool _isRoot) {
    if(_path == "") return false;
    queryXPath(_path, _isRoot);
    getNodeXPath();
    return true;
}
//===============================================
int GXml::countXPath() const {
    if(!m_xpathObj) return 0;
    if(!m_xpathObj->nodesetval) return 0;
    if(!m_xpathObj->nodesetval->nodeNr) return 0;
    int lCount = m_xpathObj->nodesetval->nodeNr;
    return lCount;
}
//===============================================
bool GXml::getNodeXPath(int _index) {
    if(!m_xpathObj) return false;
    if(!m_xpathObj->nodesetval) return false;
    if(!m_xpathObj->nodesetval->nodeNr) return false;
    m_node = m_xpathObj->nodesetval->nodeTab[_index];
    return true;
}
//===============================================
bool GXml::clearXNode() {
    for(int i = 0; i < countXPath(); i++) {
        xmlNodePtr lNode = m_xpathObj->nodesetval->nodeTab[i];
        xmlUnlinkNode(lNode);
        xmlFreeNode(lNode);
    }
    return true;
}
//===============================================
bool GXml::setAttribute(const QString& _key, const QString& _value) {
    if(!m_node) return false;
    xmlSetProp(m_node, BAD_CAST(_key.toStdString().c_str()), BAD_CAST(_value.toStdString().c_str()));
    return true;
}
//===============================================
bool GXml::saveNode() {
    m_nodeCopy.push(m_node);
    return true;
}
//===============================================
bool GXml::restoreNode() {
    m_node = m_nodeCopy.top();
    m_nodeCopy.pop();
    return true;
}
//===============================================
xmlChar* GXml::convertData(const char* _data, const char* _encoding) {
    xmlChar *out;
    int ret;
    int size;
    int out_size;
    int temp;
    xmlCharEncodingHandlerPtr handler;

    if (_data == 0)
        return 0;

    handler = xmlFindCharEncodingHandler(_encoding);

    if (!handler) {
        printf("ConvertInput: no encoding handler found for '%s'\n",
               _encoding ? _encoding : "");
        return 0;
    }

    size = (int) strlen(_data) + 1;
    out_size = size * 2 - 1;
    out = (unsigned char *) xmlMalloc((size_t) out_size);

    if (out != 0) {
        temp = size - 1;
        ret = handler->input(out, &out_size, (const xmlChar *) _data, &temp);
        if ((ret < 0) || (temp - size + 1)) {
            if (ret < 0) {
                printf("ConvertInput: conversion wasn't successful.\n");
            } else {
                printf
                    ("ConvertInput: conversion wasn't successful. converted: %i octets.\n",
                     temp);
            }

            xmlFree(out);
            out = 0;
        } else {
            out = (unsigned char *) xmlRealloc(out, out_size + 1);
            out[out_size] = 0;  /*null terminating out */
        }
    } else {
        printf("ConvertInput: no mem\n");
    }

    return out;
}
//===============================================
QString GXml::toString(const QString& _encoding, int _format) const {
    if(!m_doc) return "";
    xmlChar* lBuffer = NULL;
    int lSize;
    xmlDocDumpFormatMemoryEnc(m_doc, &lBuffer, &lSize, _encoding.toStdString().c_str(), _format);
    QString lData = (char*)lBuffer;
    xmlFree(lBuffer);
    return lData;
}
//===============================================
QString GXml::toStringNode(const QString& _encoding, int _format) const {
    if(!m_node) return "";
    xmlBufferPtr lBuffer = xmlBufferCreate();
    xmlNodeDump(lBuffer, m_doc, m_node, 0, 1);
    QString lData = (char*)lBuffer->content;
    xmlBufferFree(lBuffer);
    return lData;
}
//===============================================
