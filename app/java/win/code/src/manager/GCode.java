//===============================================
package manager;
//===============================================
import org.jdom2.Element;
//===============================================
public class GCode extends GXml {  
    //===============================================
    public GCode() {  

    }  
    //===============================================
    public Element createDatas() {
        GCode lDom = new GCode();
        lDom.m_node = getNode(String.format("/rdv/datas"));
        if(lDom.m_node == null) {
            lDom.m_node = getNode(String.format("/rdv"));
            if(lDom.m_node == null) {
                lDom.m_node = lDom.addObj("rdv");
            }
            lDom.m_node = lDom.addObj("datas");
        }
        return lDom.m_node;
    }
    //===============================================
}
//===============================================
