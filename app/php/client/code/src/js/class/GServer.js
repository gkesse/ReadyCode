//===============================================
class GServer extends GObject {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    run(_module, _method, _obj, _data) {
        if(_module == "") {
            this.m_logs.addError("Le module est obligatoire.");
        }
        else if(_module == "test") {
            this.runTest(_method, _obj, _data);
        }
        else if(_module == "logs") {
            this.runLogs(_method, _obj, _data);
        }
        else {
            this.m_logs.addError("Le module est inconnu.");
        }
    }
    //===============================================
    runTest(_method, _obj, _data) {
        var lObj = new GTest();
        lObj.run(_method, _obj, _data);
        this.m_logs.addLogs(lObj.m_logs);
    }
    //===============================================
    runLogs(_method, _obj, _data) {
        var lObj = new GLog();
        lObj.run(_method, _obj, _data);
        this.m_logs.addLogs(lObj.m_logs);
    }
    //===============================================
}
//===============================================
