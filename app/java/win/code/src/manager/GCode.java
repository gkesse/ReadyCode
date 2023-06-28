//===============================================
package manager;
//===============================================
import org.jdom2.Element;
import java.util.ArrayList;
//===============================================
public class GCode extends GXml {  
    //===============================================
    public GCode() {  

    }  
    //===============================================
    public Element createDatas() {
        GCode lDom = new GCode();
        lDom.m_node = getNode(String.format("/rdv/datas"));

        if(lDom.m_node == null) {
            lDom.m_node = getNode(String.format("/rdv"));
            if(lDom.m_node == null) {
                lDom.m_node = lDom.addObj("rdv");
            }
            lDom.m_node = lDom.addObj("datas");
        }
        
        return lDom.m_node;
    }
    //===============================================
    public Element createCode(String _code) {
        GCode lDom = new GCode();
        lDom.m_node = getNode(String.format("/rdv/datas/data[code='%s']", _code));

        if(lDom.m_node == null) {
            lDom.m_node = createDatas();
            lDom.m_node = lDom.addObj("data");
            lDom.addValue("code", _code);
        }

        return lDom.m_node;
    }
    //===============================================
    public void addData(String _code, String _name, String _value) {
        if(_value.equals("")) return;
        GCode lDom = new GCode();
        lDom.m_node = getNode(String.format("/rdv/datas/data[code='%s']/%s", _code, _name));

        if(lDom.m_node == null) {
            lDom.m_node = createCode(_code);
            lDom.addValue(_name, _value);
        }
        else {
            lDom.setValue(_value);
        }        
    }
    //===============================================
    public void addLog(String _code, ArrayList<GLog> _map) {
        int lSize = _map.size();
        if(lSize == 0) return;
        
        GCode lDom = new GCode();
        lDom.m_node = getNode(String.format("/rdv/datas/data[code='%s']/map", _code));
        
        if(lDom.m_node == null) {
            lDom.m_node = createCode(_code);
            lDom.m_node = lDom.addObj("map");
        }
        
        for(int i = 0; i < lSize; i++) {
            GLog lObj = _map.get(i);
            String lData = lObj.serialize();
            lData = toDatas(lData);
            lDom.loadNode(lData);
        }
    }
    //===============================================
    public String getData(String _code, String _name) {
        GCode lDom = new GCode();
        lDom.m_node = getNode(String.format("/rdv/datas/data[code='%s']/%s", _code, _name));
        System.out.print(String.format("/rdv/datas/data[code='%s']/%s", _code, _name));
        if(lDom.m_node == null) return "";
        return lDom.getValue();
    }
    //===============================================
    public void getLog(String _code, ArrayList<GLog> _map, GLog _obj) {
        int lSize = countNode(String.format("/rdv/datas/data[code='%s']/map/data", _code));
        if(lSize == 0) return;
        
        GCode lDom = new GCode();
        
        for(int i = 0; i < lSize; i++) {
            lDom.m_node = getNode(String.format("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code, i + 1));
            String lData = lDom.toNode();
            lData = toCode(lData);
            GLog lObj = _obj.clone();
            lObj.deserialize(lData);
            _map.add(lObj);
        }
    }
    //===============================================
    public void loadData(String _data) {
        GCode lDom = new GCode();
        lDom.m_node = createDatas();
        String lData = toDatas(_data);
        lDom.loadNode(lData);
    }
    //===============================================
    public String toDatas(String _data) {
        GCode lDom = new GCode();
        lDom.loadXml(_data);
        lDom.m_node = lDom.getNode(String.format("/rdv/datas/data"));
        if(lDom.m_node == null) return "";
        return lDom.toNode();
    }
    //===============================================
    public String toCode(String _data) {
        GCode lDom = new GCode();
        lDom.createDoc();
        lDom.m_node = lDom.createDatas();
        lDom.loadNode(_data);
        return lDom.toString();
    }
    //===============================================
}
//===============================================
