//===============================================
class GTest extends GObject {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    run(_method, _obj, _data) {
        if(_method == "") {
            this.m_logs.addError("La méthode est obligatoire.");
        }
        else if(_method == "log") {
            this.runLog(_obj, _data);
        }
        else if(_method == "xml") {
            this.runXml(_obj, _data);
        }
        else if(_method == "code") {
            this.runCode(_obj, _data);
        }
        else {
            this.m_logs.addError("La méthode est inconnue.");
        }
    }
    //===============================================
    runLog(_obj, _data) {
        // addError - addLog - addData - showLogsX
        var lLog = new GLog();
        lLog.addError("La connexion au serveur a échoué.");
        lLog.addLog("Le chargement s'est bien déroulé.");
        lLog.addData("La largeur de l'image est 1000px.");
        lLog.showLogsX();
    }
    //===============================================
    runXml(_obj, _data) {
        // toString - addObj - addData
        var lDom = new GXml();
        var lDomC1 = new GXml();
        lDom.createDoc();
        lDomC1.m_node = lDom.addObj(lDom, "datas");
        lDomC1.m_node = lDomC1.addObj(lDom, "data");
        lDomC1.addData(lDom, "code", "logs");
        lDomC1.addData(lDom, "type", "error");
        lDomC1.addData(lDom, "msg", "La connexion au serveur a échoué.");
        this.m_logs.addData(lDom.toString().toXml());
        
        // createNode
        var lDom = new GXml();
        var lDomC1 = new GXml();
        lDom.createDoc();
        lDomC1.m_node = lDom.createNode(lDom, "/rdv/datas/data");
        lDomC1.m_node = lDom.createNode(lDom, "/rdv/datas/data");
        lDomC1.createNode(lDom, "rdv/datas/data");
        lDomC1.createNode(lDom, "rdv/datas/data");
        this.m_logs.addData(lDom.toString().toXml());

        // createDatas
        var lDom = new GXml();
        var lDomC1 = new GXml();
        lDom.createDoc();
        lDomC1.m_node = lDom.createDatas();
        this.m_logs.addData(lDom.toString().toXml());
    }
    //===============================================
    runCode(_obj, _data) {
        // createDatas - createCode - addData
        var lDom = new GCode();
        lDom.createDoc();
        lDom.createDatas();
        lDom.createDatas();
        lDom.createCode("logs");
        lDom.createCode("logs");
        lDom.addData("logs", "type", "error");
        lDom.addData("logs", "msg", "La connexion au serveur a echoué.");
        lDom.addData("logs", "type", "error_2");
        lDom.addData("logs", "msg", "La connexion au serveur a echoué_2.");
        this.m_logs.addData(lDom.toString().toXml());
        
        // addError - addLog - addData
        var lLog = new GLog();
        lLog.addError("La connexion au serveur a échoué.");
        lLog.addLog("Le chargement s'est bien déroulé.");
        lLog.addData("La largeur de l'image est 1000px.");
        lLog.loadFromMap(3);
        this.m_logs.addData(lLog.serialize().toXml());
        
        // addError - addLog - addData
        var lLog2 = new GLog();
        lLog2.deserialize(lLog.serialize());
        this.m_logs.addData(lLog2.serialize().toXml());
    }
    //===============================================
}
//===============================================
