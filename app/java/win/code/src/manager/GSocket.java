//===============================================
package manager;
//===============================================
import java.net.Socket;
import java.net.ServerSocket;
//===============================================
public class GSocket extends GObject {  
    //===============================================
    public GSocket() {  

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
            Socket lClient = null;
            try {
                lClient = lServer.accept();
            }
            catch(Exception e) {
                m_logs.addError("La connexion d'un client a échoué.");
            }
        }
    }
    //===============================================
}
//===============================================
