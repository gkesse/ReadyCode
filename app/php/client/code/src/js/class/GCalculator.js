//===============================================
class GCalculator extends GObject {
    //===============================================
    constructor() {
        super();
        this.m_expression = "";
    }
    //===============================================
    readExpression() {
        var lObj = document.getElementById("CalculatorExpression");
        var lData = lObj.value;
        return lData;
    }
    //===============================================
    serialize(_code = "calculator") {
        var lDom = new GCode();
        lDom.createDoc();
        lDom.addData(_code, "expression", utf8_to_b64(this.m_expression));
        return lDom.toString();
    }
    //===============================================
    deserialize(_data, _code = "calculator") {
        var lDom = new GCode();
        lDom.loadXml(_data);
        this.m_expression = b64_to_utf8(lDom.getData(_code, "expression"));
        lDom.getMap(_code, this);
    }
    //===============================================
    run(_method, _obj, _data) {
        if(_method == "") {
            this.m_logs.addError("La méthode est obligatoire.");
        }
        else if(_method == "run_calculator") {
            this.onRunCalculator(_obj, _data);
        }
        else {
            this.m_logs.addError("La méthode est inconnue.");
        }
    }
    //===============================================
    onRunCalculator(_obj, _data) {
        var lEvent = _data;
        if(lEvent.key == "Enter") {
            this.m_expression = this.readExpression();
            var lData = this.serialize();
            var lAjax = new GAjax();
            lAjax.callRemote("calculator", "run_calculator", lData, this.onRunCalculatorCB);        
        }
    }
    //===============================================
    onRunCalculatorCB(_data, _isOk) {
        if(_isOk) {

        }
    }
    //===============================================
}
//===============================================
