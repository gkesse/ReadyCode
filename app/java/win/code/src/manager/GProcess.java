//===============================================
package manager;

import org.mariuszgromada.math.mxparser.License;
import org.mariuszgromada.math.mxparser.mXparser;

//===============================================
public class GProcess extends GObject {  
    //===============================================
    public GProcess() {  

    }  
    //===============================================
    public void init() {
    	
    }
    //===============================================
    public void clean() {
    	
    }
    //===============================================
    public void toMxParserLicence() {
    	/* Non-Commercial Use Confirmation */
    	boolean isCallSuccessful = License.iConfirmNonCommercialUse("Gerard KESSE");
    	 
    	/* Verification if use type has been already confirmed */
    	boolean isConfirmed = License.checkIfUseTypeConfirmed();
    	 
    	/* Checking use type confirmation message */
    	String message = License.getUseTypeConfirmationMessage();
    	 
    	/* ----------- */
    	mXparser.consolePrintln("isCallSuccessful = " + isCallSuccessful);
    	mXparser.consolePrintln("isConfirmed = " + isConfirmed);
    	mXparser.consolePrintln("message = " + message);
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
    	toMxParserLicence();
        GSocket lObj = new GSocket();
        lObj.runServer();
        m_logs.addLogs(lObj.getLogs());
    }
    //===============================================
}
//===============================================
