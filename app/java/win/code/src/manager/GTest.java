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
        else if(lMethod.equals("log")) {
            runLog(_args);
        }
        else if(lMethod.equals("socket")) {
            runSocket(_args);
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
        
        // createDatas - createCode - addData
        lDom.createDoc();
        lDom.createDatas();
        lDom.createDatas();
        lDom.createCode("logs");
        lDom.createCode("logs");
        lDom.addData("logs", "type", "error");
        lDom.addData("logs", "side", "server_java");
        lDom.addData("logs", "msg", "La connexion au serveur a échoué.");
        lDom.addData("logs", "type", "log");
        lDom.print();
    }
    //===============================================
    public void runLog(String[] _args) {
        GLog lLog = new GLog();
        GLog lLogC = new GLog();
        
        // addError - createCode - addData - print
        lLog.addError("La connexion au serveur a échoué.");
        lLog.addLog("Le module a été chargé.");
        lLog.addData("La résolution de l'appareil est : 970 x 1250.");
        lLog.loadFromMap(3);
        lLog.print();
        
        // serialize - deserialize
        lLogC.deserialize(lLog.serialize());
        lLogC.print();
    }
    //===============================================
    public void runSocket(String[] _args) {
        GSocket lClient = new GSocket();
        String lData = lClient.callServer("Bonjour tout le monde.");
        m_logs.addLogs(lClient.getLogs());
        System.out.print(String.format("%s\n", lData));
    }
    //===============================================
}
//===============================================
