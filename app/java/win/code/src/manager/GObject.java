//===============================================
package manager;
//===============================================
import java.util.ArrayList;
//===============================================
public class GObject {  
    //===============================================
    protected GLog m_logs = new GLog();
    protected GCode m_resp = new GCode();
    protected ArrayList<GObject> m_map = new ArrayList<GObject>();
    //===============================================
    public GObject() {
        m_resp.createDoc();
    }  
    //===============================================
    public GLog getLogs() {
        return m_logs;
    }  
    //===============================================
    public void runThread() {
        
    }  
    //===============================================
}
//===============================================
