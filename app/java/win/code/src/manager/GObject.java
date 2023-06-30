//===============================================
package manager;
//===============================================
import java.util.ArrayList;
import java.util.Base64;
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
    public String toBase64(String _data) {
        return Base64.getEncoder().encodeToString(_data.getBytes());
    }
    //===============================================
    public String fromBase64(String _data) {
        return new String(Base64.getDecoder().decode(_data));
    }
    //===============================================
    public GObject clone() {return new GObject();}  
    public void runThread() {}  
    public String serialize() {return "";}
    public void deserialize(String _data) {}
    //===============================================
}
//===============================================
