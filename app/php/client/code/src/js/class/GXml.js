//===============================================
class GXml {
    //===============================================
    constructor() {
        this.m_doc = null;
        this.m_node = null;
    }
    //===============================================
    createDoc() {
        var lXml = sprintf("<?xml version='1.0' encoding='UTF-8'?><rdv></rdv>");
        var lParser = new DOMParser();
        this.m_doc = lParser.parseFromString(lXml, "text/xml");
        this.m_node = this.m_doc.firstElementChild;
    }
    //===============================================
    addObj(_root, _name) {
        if(!_root.m_doc) return null;
        if(!this.m_node) return null;
        var lNode = _root.m_doc.createElement(_name);
        this.m_node.appendChild(lNode);
        return lNode;
    }    
    //===============================================
    addData(_root, _name, _value, _isCData = false) {
        if(!_root.m_doc) return null;
        if(!this.m_node) return null;
        var lDom = new GXml();
        lDom.m_node = _root.m_doc.createElement(_name);
        lDom.setValue(_root, _value, _isCData);
        this.m_node.appendChild(lDom.m_node);
        return this.m_node;
    }    
    //===============================================
    setValue(_root, _value, _isCData = false) {
        if(!_root.m_doc) return;
        if(!this.m_node) return;
        if(!_isCData) {
            this.m_node.innerHTML = _value;
        }
        else {
            var lCData = _root.m_doc.createCDATASection(_value);
            this.m_node.appendChild(lCData);
        }
    }
    //===============================================
    toString() {
        if(!this.m_doc) return "";
        if(!this.m_node) return "";
        var lData = this.m_doc.documentElement.outerHTML;
        lData = sprintf("<?xml version='1.0' encoding='UTF-8'?>\n%s", lData);
        return lData;
    }
    //===============================================
    toNode() {
        if(!this.m_node) return "";
        var lData = this.m_node.outerHTML;
        return lData;
    }
    //===============================================
}
//===============================================
