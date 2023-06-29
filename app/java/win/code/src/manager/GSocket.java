//===============================================
package manager;
//===============================================
import java.net.Socket;
import java.net.ServerSocket;
import java.net.InetAddress;
import java.io.InputStream;
import java.io.DataOutputStream;
import java.nio.charset.StandardCharsets;
//===============================================
public class GSocket extends GObject {  
    //===============================================
    static final int BUFFER_SIZE = 1024;
    static final int BUFFER_MAX = 1*1024*1024; // 1 Mo
    //===============================================
    Socket m_socket = null;
    GLog m_srvLogs = new GLog();
    boolean m_continue = true;
    //===============================================
    public GSocket() {  

    }  
    //===============================================
    public String readData() {
        String lData = "";
        try {
            InputStream lStreamIn = m_socket.getInputStream();
            while(true) {
                byte[] lBuffer = new byte[BUFFER_SIZE];
                int lBytes = lStreamIn.read(lBuffer);
                if(lBytes == -1) break;
                lData += new String(lBuffer, 0, lBytes, StandardCharsets.UTF_8);
                if(lStreamIn.available() <= 0) break;
                if(lData.length() >= BUFFER_MAX) {
                	m_srvLogs.addError("La limite des données est atteinte.");
                    break;
                }
            }
        }
        catch(Exception e) {
        	m_srvLogs.addError("La lecture des données a échoué.");
        }
        return lData;
    }
    //===============================================
    public void sendData(String _data) {
        try {
            DataOutputStream lStreamOut = new DataOutputStream(m_socket.getOutputStream());
            lStreamOut.write(_data.getBytes());
        }
        catch(Exception e) {
        	m_srvLogs.addError("L'envoi des données a échoué.");
        }
    }
    //===============================================
    public void closeSocket() {
        try {
            m_socket.close();
        }
        catch(Exception e) {
        	m_srvLogs.addError("La fermeture du socket a échoué.");
        }
    }
    //===============================================
    public void runServer() {
        int lPort = 9040;
        ServerSocket lServer = null;
        
        try {            
        	lServer = new ServerSocket(lPort);
            
            System.out.print(String.format("Démarrage du serveur...\n"));
            
            while(true) {
                if(!m_continue) break;
                
                GSocket lClient = new GSocket();
                
                try {
                    lClient.m_socket = lServer.accept();
                }
                catch(Exception e) {
                	m_srvLogs.addError("La connexion au serveur a échoué.");
                    break;
                }
                                
                GThread lThread = new GThread();
                lThread.setObj(lClient);
                lThread.start();
            }
            
            System.out.print(String.format("Arrêt du serveur...\n"));

            lServer.close();
        }
        catch(Exception e) {
        	m_srvLogs.addError("Le démarrage du serveur a échoué.");
        }
        
        if(m_srvLogs.hasErrors()) {
        	m_logs.addLogs(m_srvLogs);
        }
    }
    //===============================================
    public void runThread() {
        GSocket lClient = this;
        String lData = lClient.readData();
        GServer lServer = new GServer();
        lServer.run(lData);
        lServer.sendResponse(lClient);
        lClient.closeSocket();
    }  
    //===============================================
    public String callFacade(String _module, String _method, String _data) {
        GCode lDom = new GCode();
        lDom.createDoc();
        lDom.addData("manager", "module", _module);
        lDom.addData("manager", "method", _method);
        lDom.loadData(_data);
        String lData = lDom.toString();
        return callServer(lData);
    }
    //===============================================
    public String callServer(String _data) {
        String lAddress = "127.0.0.1";
        int lPort = 9040;
        String lDataOut = "";
        
        try {
            InetAddress lInetAddress = InetAddress.getByName(lAddress);
            m_socket = new Socket(lInetAddress, lPort);
            sendData(_data);
            lDataOut = readData();
            closeSocket();
        }
        catch(Exception e) {
        	m_srvLogs.addError("La connexion au serveur a échoué.");
        }
        
        if(m_srvLogs.hasErrors()) {
        	m_logs.addError("La connexion au serveur a échoué.");
        }
        
        return lDataOut;
    }
    //===============================================
}
//===============================================
