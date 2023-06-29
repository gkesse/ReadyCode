//===============================================
package manager;
//===============================================
public class GManager extends GObject {  
    //===============================================
    protected String m_module = "";
    protected String m_method = "";
    //===============================================
    public GManager() {  

    }  
    //===============================================
    public String serialize() {
        String lCode = "manager";
        GCode lDom = new GCode();
        lDom.createDoc();
        lDom.addData(lCode, "module", m_module);
        lDom.addData(lCode, "method", m_method);
        return lDom.toString();
    }
    //===============================================
    public void deserialize(String _data) {
        String lCode = "manager";
        GCode lDom = new GCode();
        lDom.loadXml(_data);
        m_module = lDom.getData(lCode, "module");
        m_method = lDom.getData(lCode, "method");
    }
    //===============================================
}
//===============================================
