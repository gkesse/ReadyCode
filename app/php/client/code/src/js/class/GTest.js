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

    }
    //===============================================
}
//===============================================
