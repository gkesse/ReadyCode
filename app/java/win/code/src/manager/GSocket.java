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
    //===============================================
    Socket m_socket = null;
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
                lData += new String(lBuffer, StandardCharsets.UTF_8);
                if(lStreamIn.available() <= 0) break;
            }
        }
        catch(Exception e) {
            m_logs.addError("La connexion au serveur a échoué.");
        }
        return lData;
    }
    //===============================================
    public void sendData(String _data) {
        try {
            DataOutputStream dOut = new DataOutputStream(m_socket.getOutputStream());
            dOut.write(_data.getBytes());
        }
        catch(Exception e) {
            m_logs.addError("La connexion au serveur a échoué.");
        }
    }
    //===============================================
    public void closeSocket() {
        try {
            m_socket.close();
        }
        catch(Exception e) {
            m_logs.addError("La connexion au serveur a échoué.");
        }
    }
    //===============================================
    public void runServer() {
        int lPort = 9040;
        ServerSocket lServer = null;
        
        try {
            lServer = new ServerSocket(lPort);
        }
        catch(Exception e) {
            m_logs.addError("Le démarrage du serveur a échoué.");
        }
        
        System.out.print(String.format("Démarrage du serveur...\n"));

        while(true) {
            GSocket lClient = new GSocket();
            try {
                lClient.m_socket = lServer.accept();
            }
            catch(Exception e) {
                m_logs.addError("La connexion au serveur a échoué.");
            }
            
            GThread lThread = new GThread();
            lThread.setObj(lClient);
            lThread.start();
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
            m_logs.addError("La connexion au serveur a échoué.");
        }
        
        return lDataOut;
    }
    //===============================================
}
//===============================================
