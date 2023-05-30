//===============================================
class GLog {
    //===============================================
    constructor() {
        this.m_type = "";
        this.m_side = "";
        this.m_msg = "";
        this.m_map = [];
    }
    //===============================================
    clone() {
        return new GLog();
    }
    //===============================================
    setObj(_obj) {
        this.m_type = _obj.m_type;
        this.m_side = _obj.m_side;
        this.m_msg = _obj.m_msg;
    }
    //===============================================
    clearMap() {
        this.m_map = [];
    }
    //===============================================
    addError(_msg) {
        var lObj = new GLog();
        lObj.m_type = "error";
        lObj.m_side = "client";
        lObj.m_msg = _msg;
        this.m_map.push(lObj);
    }
    //===============================================
    addLog(_msg) {
        var lObj = new GLog();
        lObj.m_type = "log";
        lObj.m_side = "client";
        lObj.m_msg = _msg;
        this.m_map.push(lObj);
    }
    //===============================================
    addData(_msg) {
        var lObj = new GLog();
        lObj.m_type = "data";
        lObj.m_side = "client";
        lObj.m_msg =  _msg;
        this.m_map.push(lObj);
    }
    //===============================================
    addLogs(_obj) {
        for(var i = 0; i < _obj.m_map.length; i++) {
            var lObj = _obj.m_map[i];
            var lNew = new GLog();
            lNew.setObj(lObj);
            this.m_map.push(lNew);
        }
    }
    //===============================================
    hasErrors() {
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type == "error") return true;
        }
        return false;
    }
    //===============================================
    hasLogs() {
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type == "log") return true;
        }
        return false;
    }
    //===============================================
    hasDatas() {
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type == "data") return true;
        }
        return false;
    }
    //===============================================
    getErrors() {
        var lErrors = "";
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type != "error") continue;
            var lError = lObj.m_msg;
            if(i != 0) lErrors += "<br>";
            lError = sprintf("<i class='fa fa-chevron-right'></i> %s", lError);
            lErrors += lError;
        }
        return lErrors;
    }
    //===============================================
    getLogs() {
        var lLogs = "";
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type != "log") continue;
            var lLog = lObj.m_msg;
            if(i != 0) lLogs += "<br>";
            lLog = sprintf("<i class='fa fa-chevron-right'></i> %s", lLog);
            lLogs += lLog;
        }
        return lLogs;
    }
    //===============================================
    getDatas() {
        var lDatas = "";
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type != "data") continue;
            var lData = lObj.m_msg;
            if(i != 0) lDatas += "<br>";
            lData = sprintf("<xmp>%s</xmp>\n", lData);
            lDatas += lData;
        }
        return lDatas;
    }
    //===============================================
    showErrors() {
        if(!this.hasErrors()) return;
        if(this.hasDatas()) return;
        
        var lLogTitle = document.getElementById("LogTitle");
        var lLogIntro = document.getElementById("LogIntro");
        var lLogBody = document.getElementById("LogBody");

        lLogTitle.innerHTML = "Erreurs";
        lLogIntro.innerHTML = "Consultez les erreurs.";
        lLogBody.innerHTML = this.getErrors();

        var lLogModal = document.getElementById("LogModal");
        var lLogForm = document.getElementById("LogForm");
        
        lLogForm.classList.remove("AnimateHide");
        lLogForm.classList.add("AnimateShow");
        lLogModal.style.display = "block";
    }
    //===============================================
    showLogs() {
        if(!this.hasLogs()) return;
        if(this.hasDatas()) return;
        if(this.hasErrors()) return;
        
        var lLogTitle = document.getElementById("LogTitle");
        var lLogIntro = document.getElementById("LogIntro");
        var lLogBody = document.getElementById("LogBody");

        lLogTitle.innerHTML = "Logs";
        lLogIntro.innerHTML = "Consultez les logs.";
        lLogBody.innerHTML = this.getLogs();

        var lLogModal = document.getElementById("LogModal");
        var lLogForm = document.getElementById("LogForm");
        
        lLogForm.classList.remove("AnimateHide");
        lLogForm.classList.add("AnimateShow");
        lLogModal.style.display = "block";
    }
    //===============================================
    showDatas() {
        if(!this.hasDatas()) return;
        
        var lLogTitle = document.getElementById("LogTitle");
        var lLogIntro = document.getElementById("LogIntro");
        var lLogBody = document.getElementById("LogBody");

        lLogTitle.innerHTML = "Datas";
        lLogIntro.innerHTML = "Consultez les données.";
        lLogBody.innerHTML = this.getDatas();

        var lLogModal = document.getElementById("LogModal");
        var lLogForm = document.getElementById("LogForm");
        
        lLogForm.classList.remove("AnimateHide");
        lLogForm.classList.add("AnimateShow");
        lLogModal.style.display = "block";
    }
    //===============================================
    showLogsX() {
        this.showDatas();
        this.showErrors();
        this.showLogs();
    }
    //===============================================
    run(_method, _obj, _data) {
        if(_method == "close_logs") {
            this.onCloseLogs(_obj, _data);
        }
    }
    //===============================================
    onCloseLogs(_obj, _data) {
        var lLogModal = document.getElementById("LogModal");
        var lLogForm = document.getElementById("LogForm");
        
        lLogForm.classList.remove("AnimateShow");
        lLogForm.classList.add("AnimateHide");

        setTimeout(function() {
            lLogModal.style.display = "none";
        }, 400);
    }
    //===============================================
}
//===============================================
