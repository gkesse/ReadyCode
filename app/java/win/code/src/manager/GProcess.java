//===============================================
package manager;
//===============================================
public class GProcess extends GObject {  
    //===============================================
    public GProcess() {  

    }  
    //===============================================
    public void run(String[] _args) {
        String lModule = "";
        if(_args.length > 0) lModule = _args[0];
        
        if(lModule.equals("")) {
            m_logs.addError("Le module est obligatoire.");
        }
        else if(lModule.equals("test")) {
            runTest(_args);
        }
        else if(lModule.equals("server")) {
            runServer(_args);
        }
        else {
            m_logs.addError("Le module est inconnu.");
        }
    }        
    //===============================================
    public void runTest(String[] _args) {
        GTest lObj = new GTest();
        lObj.run(_args);
        m_logs.addLogs(lObj.getLogs());
    }
    //===============================================
    public void runServer(String[] _args) {
        GSocket lObj = new GSocket();
        lObj.runServer();
        m_logs.addLogs(lObj.getLogs());
    }
    //===============================================
}
//===============================================
