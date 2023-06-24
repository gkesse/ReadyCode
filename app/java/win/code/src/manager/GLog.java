//===============================================
package manager;
//===============================================
import java.util.ArrayList;
//===============================================
public class GLog {
    //===============================================
    private String m_type;
    private String m_side;
    private String m_msg;
    private ArrayList<GLog> m_map = new ArrayList<GLog>();
    //===============================================
    public GLog() {

    }
    //===============================================
    public void setObj(GLog _obj) {
        m_type = _obj.m_type;
        m_side = _obj.m_side;
        m_msg = _obj.m_msg;
    }
    //===============================================
    public void addError(String _msg) {
        GLog lObj = new GLog();
        lObj.m_type = "error";
        lObj.m_side = "server_java";
        lObj.m_msg = _msg;
        m_map.add(lObj);
    }
    //===============================================
    public void addLog(String _msg) {
        GLog lObj = new GLog();
        lObj.m_type = "log";
        lObj.m_side = "server_java";
        lObj.m_msg = _msg;
        m_map.add(lObj);
    }
    //===============================================
    public void addData(String _msg) {
        GLog lObj = new GLog();
        lObj.m_type = "data";
        lObj.m_side = "server_java";
        lObj.m_msg = _msg;
        m_map.add(lObj);
    }
    //===============================================
    public void addLogs(GLog _obj) {
        for(int i = 0; i < _obj.m_map.size(); i++) {
            GLog lObj = _obj.m_map.get(i);
            GLog lNew = new GLog();
            lNew.setObj(lObj);
            m_map.add(lNew);
        }
    }
    //===============================================
    public boolean hasErrors() {
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            if(lObj.m_type.equals("error")) return true;
        }
        return false;
    }
    //===============================================
    public boolean hasLogs() {
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            if(lObj.m_type.equals("log")) return true;
        }
        return false;
    }
    //===============================================
    public boolean hasDatas() {
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            if(lObj.m_type.equals("data")) return true;
        }
        return false;
    }
    //===============================================
    public void showErrors() {
        if(hasDatas()) return;
        if(!hasErrors()) return;
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            if(!lObj.m_type.equals("error")) continue;
            System.out.print(String.format("[%s] : %s\n", lObj.m_type, lObj.m_msg));
        }
    }
    //===============================================
    public void showLogs() {
        if(hasDatas()) return;
        if(hasErrors()) return;
        if(!hasLogs()) return;
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            if(!lObj.m_type.equals("log")) continue;
            System.out.print(String.format("[%s] : %s\n", lObj.m_type, lObj.m_msg));
        }
    }
    //===============================================
    public void showDatas() {
        if(!hasDatas()) return;
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            if(!lObj.m_type.equals("data")) continue;
            System.out.print(String.format("[%s] : %s\n", lObj.m_type, lObj.m_msg));
        }
    }
    //===============================================
    public void showLogsX() {
        showErrors();
        showLogs();
        showDatas();
    }
    //===============================================
    public void print() {
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            System.out.print(String.format("[%s] : %s\n", lObj.m_type, lObj.m_msg));
        }
    }
    //===============================================
}
//===============================================
