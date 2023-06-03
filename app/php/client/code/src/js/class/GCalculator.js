//===============================================
class GCalculator extends GObject {
    //===============================================
    constructor() {
        super();
        this.m_expression = "";
        this.m_result = "";
    }
    //===============================================
    readExpression() {
        var lExpression = document.getElementById("CalculatorExpression");
        var lData = lExpression.value;
        return lData;
    }
    //===============================================
    writeResult() {
        var lOutput = document.getElementById("CalculatorOutput");
        var lHtml = "";
        lHtml += sprintf("<div class='Calculator4'>\n");
        lHtml += sprintf("<div class='Calculator5'>%s</div>\n", this.m_expression);
        lHtml += sprintf("<div class='Calculator6'>= %s</div>\n", this.m_result);
        lHtml += sprintf("</div>\n");
        lOutput.innerHTML += lHtml;
    }
    //===============================================
    serialize(_code = "calculator") {
        var lDom = new GCode();
        lDom.createDoc();
        lDom.addData(_code, "expression", utf8_to_b64(this.m_expression));
        lDom.addData(_code, "result", this.m_result);
        return lDom.toString();
    }
    //===============================================
    deserialize(_data, _code = "calculator") {
        var lDom = new GCode();
        lDom.loadXml(_data);
        this.m_expression = b64_to_utf8(lDom.getData(_code, "expression"));
        this.m_result = lDom.getData(_code, "result");
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
            var lObj = new GCalculator();
            lObj.deserialize(_data);
            lObj.writeResult();
        }
    }
    //===============================================
}
//===============================================
