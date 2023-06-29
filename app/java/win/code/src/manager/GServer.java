//===============================================
package manager;
//===============================================
public class GServer extends GManager {  
    //===============================================
	GLog m_srvLogs = new GLog();
    //===============================================
    public GServer() {  

    }  
    //===============================================
    public boolean isValid(String _data) {
    	if(_data.equals("")) {
    		m_srvLogs.addError("La requête est vide.");
    		return false;
    	}
    	GCode lDom = new GCode();
    	if(!lDom.loadXml(_data)) {
    		m_srvLogs.addError("La requête n'est pas valide.");
    		return false;
    	}
    	if(!lDom.hasDatas()) {
    		m_srvLogs.addError("Le format de la requête n'est pas valide.");
    		return false;
    	}
        return true;
    }        
    //===============================================
    public void sendResponse(GSocket _socket) {
        GSocket lClient = _socket;
        if(!m_srvLogs.hasErrors()) {
            m_resp.loadData(m_logs.serialize());
            if(!m_resp.hasDatas()) return;
            lClient.sendData(m_resp.toString());        	
        }
        else {
            lClient.sendData("La connexion au serveur a échoué.");        	
        }
    }        
    //===============================================
    public void run(String _data) {
    	if(!isValid(_data)) return;
        deserialize(_data);
        if(m_module.equals("")) {
        	m_logs.addError("Le module est obligatoire.");
        }
        else if(m_module.equals("calculator")) {
        	runCalculator(_data);
        }
        else {
        	m_logs.addError("Le module est inconnue.");
        }
    }        
    //===============================================
    public void runCalculator(String _data) {
    	GCalculator lObj = new GCalculator();
    	lObj.run(_data);
    	m_logs.addLogs(lObj.getLogs());
    	m_resp.loadData(lObj.serialize());
    }
    //===============================================
}
//===============================================
