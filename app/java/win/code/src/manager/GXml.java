//===============================================
package manager;
//===============================================
import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.input.SAXBuilder;
import org.jdom2.output.XMLOutputter;
import org.jdom2.output.Format;
import org.jdom2.xpath.XPathExpression;
import org.jdom2.xpath.XPathFactory;
import org.jdom2.filter.Filters;
import javax.xml.XMLConstants;
import java.io.File;
import java.io.StringReader;
import java.util.List;
//===============================================
public class GXml {
    //===============================================
    protected Document m_doc = null;
    protected Element m_node = null;
    protected GLog m_logs = new GLog();
    //===============================================
    public GXml() {

    }
    //===============================================
    public GLog getLogs() {
        return m_logs;
    }
    //===============================================
    public void setNode(Element _node) {
        m_node = _node;
    }
    //===============================================
    public void createDoc() {
        m_doc = new Document();
        m_node = new Element("rdv");
        m_doc.addContent(m_node);
    }
    //===============================================
    public boolean loadXml(String _data) {
        try {
            SAXBuilder lSax = new SAXBuilder();
            m_doc = lSax.build(new StringReader(_data));
            m_node = m_doc.getRootElement();
        }
        catch (Exception e) {
            m_logs.addError("La création du document a échoué.");
        }
        return !m_logs.hasErrors();
    }
    //===============================================
    public boolean loadFile(String _filename) {
        try {
            SAXBuilder lSax = new SAXBuilder();
            lSax.setProperty(XMLConstants.ACCESS_EXTERNAL_DTD, "");
            lSax.setProperty(XMLConstants.ACCESS_EXTERNAL_SCHEMA, "");
            m_doc = lSax.build(new File(_filename));
            m_node = m_doc.getRootElement();
        }
        catch(Exception ex) {
            m_logs.addError("Le chargement du fichier a échoué.");
        }
        return !m_logs.hasErrors();
    }
    //===============================================
    public Element addObj(String _name) {
        Element lNode = new Element(_name);
        m_node.addContent(lNode);
        return lNode;
    }
    //===============================================
    public Element addValue(String _name, String _value) {
        Element lNode = new Element(_name);
        lNode.setText(_value);
        m_node.addContent(lNode);
        return m_node;
    }
    //===============================================
    public Element createNode(String _path) {
        String[] lPaths = _path.split("/");
        String lPath = "/";
        GXml lDom = new GXml();
        lDom.m_node = m_node;
        for(int i = 0, j = 0; i < lPaths.length; i++) {
            String lPathI = lPaths[i];
            if(lPathI.equals("")) continue;
            if(j++ != 0) lPath += "/";
            lPath += lPathI;
            if(!existNode(lPath)) {
                lDom.m_node = lDom.addObj(lPathI);
            }
            else {
                lDom.m_node = getNode(lPath);
            }
        }
        return lDom.m_node;
    }
    //===============================================
    public boolean existNode(String _path) {
        return (countNode(_path) != 0);
    }
    //===============================================
    public int countNode(String _path) {
        if(m_doc == null) return 0;
        XPathFactory lXPathF = XPathFactory.instance();
        XPathExpression lXPathE = lXPathF.compile(_path, Filters.element());
        List<Element> lNodes = lXPathE.evaluate(m_node);
        return lNodes.size();
    }
    //===============================================
    public Element getNode(String _path) {
        if(m_doc == null) return null;
        XPathFactory lXPathF = XPathFactory.instance();
        XPathExpression lXPathE = lXPathF.compile(_path, Filters.element());
        List<Element> lNodes = lXPathE.evaluate(m_node);
        if(lNodes.size() == 0) return null;
        return lNodes.get(0);
    }
    //===============================================
    public String toString() {
        if(m_doc == null) return "";
        XMLOutputter lXmlOut = new XMLOutputter(Format.getPrettyFormat());
        String lData = lXmlOut.outputString(m_doc);
        return lData;
    }
    //===============================================
    public String toNode() {
        if(m_node == null) return "";
        XMLOutputter lXmlOut = new XMLOutputter(Format.getPrettyFormat());
        String lData = lXmlOut.outputString(m_node);
        return lData;
    }
    //===============================================
    public void print() {
        System.out.print(String.format("%s\n", toString()));
    }
    //===============================================
    public void printNode() {
        System.out.print(String.format("%s\n", toNode()));
    }
    //===============================================
}
//===============================================
