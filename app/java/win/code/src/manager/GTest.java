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
        else if(lMethod.equals("test")) {
            runTest(_args);
        }
        else {
            m_logs.addError("La méthode est inconnue.");
        }
    }        
    //===============================================
    public void runTest(String[] _args) {
        
    }
    //===============================================
}
//===============================================
