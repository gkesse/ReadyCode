//===============================================
package manager;
//===============================================
import java.util.ArrayList;
//===============================================
public class GLog {
    //===============================================
    private String m_type = "";
    private String m_side = "";
    private String m_msg = "";
    private ArrayList<GLog> m_map = new ArrayList<GLog>();
    //===============================================
    public GLog() {

    }
    //===============================================
    public GLog clone() {
        return new GLog();
    }
    //===============================================
    public void setObj(GLog _obj) {
        m_type = _obj.m_type;
        m_side = _obj.m_side;
        m_msg = _obj.m_msg;
    }
    //===============================================
    public GLog loadToMap(int i) {
        if(i >= 1 && i <= m_map.size()) {
            GLog lObj = m_map.get(i - 1);
            lObj.setObj(this);
        }
        return this;
    }
    //===============================================
    public GLog loadFromMap(int i) {
        if(i >= 1 && i <= m_map.size()) {
            GLog lObj = m_map.get(i - 1);
            setObj(lObj);
        }
        return this;
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
            System.out.print(String.format("[%-5s] : %s\n", lObj.m_type, lObj.m_msg));
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
            System.out.print(String.format("[%-5s] : %s\n", lObj.m_type, lObj.m_msg));
        }
    }
    //===============================================
    public void showDatas() {
        if(!hasDatas()) return;
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            if(!lObj.m_type.equals("data")) continue;
            System.out.print(String.format("[%-5s] : %s\n", lObj.m_type, lObj.m_msg));
        }
    }
    //===============================================
    public void showLogsX() {
        showErrors();
        showLogs();
        showDatas();
    }
    //===============================================
    public void showLogsA() {
        for(int i = 0; i < m_map.size(); i++) {
            GLog lObj = m_map.get(i);
            System.out.print(String.format("[%-5s] : %s\n", lObj.m_type, lObj.m_msg));
        }
    }
    //===============================================
    public void print() {
        System.out.print(String.format("%s\n", serialize()));
    }
    //===============================================
    public String serialize() {
        String lCode = "logs";
        GCode lDom = new GCode();
        lDom.createDoc();
        lDom.addData(lCode, "type", m_type);
        lDom.addData(lCode, "side", m_side);
        lDom.addData(lCode, "msg", m_msg);
        lDom.addLog(lCode, m_map);
        return lDom.toString();
    }
    //===============================================
    public void deserialize(String _data) {
        String lCode = "logs";
        GCode lDom = new GCode();
        lDom.loadXml(_data);
        m_type = lDom.getData(lCode, "type");
        m_side = lDom.getData(lCode, "side");
        m_msg = lDom.getData(lCode, "msg");
        lDom.getLog(lCode, m_map, this);
    }
    //===============================================
}
//===============================================
