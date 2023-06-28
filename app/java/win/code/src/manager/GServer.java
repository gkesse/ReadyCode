//===============================================
package manager;
//===============================================
public class GServer extends GManager {  
    //===============================================
    public GServer() {  

    }  
    //===============================================
    public void sendResponse(GSocket _socket) {
        GSocket lClient = _socket;
        m_resp.loadData(m_logs.serialize());
        lClient.sendData(m_resp.toString());
    }        
    //===============================================
    public void run(String _data) {
        System.out.print(String.format("%s\n", _data));
        deserialize(_data);
        m_logs.addError(m_module + " - " + m_method);
    }        
    //===============================================
}
//===============================================
