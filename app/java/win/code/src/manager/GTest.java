//===============================================
package manager;
//===============================================
public class GTest extends GObject {  
    //===============================================
    public GTest() {  

    }  
    //===============================================
    public void run(String[] _args) {
        String lMethod = "";
        if(_args.length > 1) lMethod = _args[1];
        
        if(lMethod.equals("")) {
            m_logs.addError("La méthode est obligatoire.");
        }
        else if(lMethod.equals("xml")) {
            runXml(_args);
        }
        else if(lMethod.equals("code")) {
            runCode(_args);
        }
        else {
            m_logs.addError("La méthode est inconnue.");
        }
    }        
    //===============================================
    public void runXml(String[] _args) {
        GXml lDom = new GXml();
        GXml lDomC = new GXml();
        String lData = "";
        
        // createDoc - addObj - addValue - toString - setNode - print
        lDom.createDoc();
        lDomC.setNode(lDom.addObj("datas"));
        lDomC.setNode(lDomC.addObj("data"));
        lDomC.addValue("code", "logs");
        lData = lDom.toString();
        lDom.print();
        
        // loadXml
        lDom.loadXml(lData);
        lDomC.setNode(lDom.getNode("/rdv/datas"));
        lDomC.printNode();

        // loadXml
        lDom.createDoc();
        lDom.createNode("/rdv/datas/data");
        lDom.createNode("/rdv/datas/data");
        lDom.print();
    }
    //===============================================
    public void runCode(String[] _args) {
        GCode lDom = new GCode();
        
        //
        lDom.createDoc();
        lDom.print();
    }
    //===============================================
}
//===============================================
