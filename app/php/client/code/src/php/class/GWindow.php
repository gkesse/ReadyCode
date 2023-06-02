<?php   
//===============================================
class GWindow extends GObject {
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function run($_module, $_method) {
        if($_method == "calculator") {
            $this->runCalculator($_module, $_method);
        }
    }
    //===============================================
    public function runCalculator($_module, $_method) {
        echo sprintf("runCalculator...<br>\n");
        echo sprintf("<div class='Calculator1'>\n");
        echo sprintf("<div class='Calculator2'>\n");
        echo sprintf("<input id='CalculatorExpression' type='text' onkeyup='call_server(\"calculator\", \"run_calculator\", this, event)'/>\n");
        echo sprintf("</div>\n");
        echo sprintf("</div>\n");
    }
    //===============================================
 }
//===============================================
?>
