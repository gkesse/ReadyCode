<?php
//===============================================
class GCalculator extends GManager {
    //===============================================
    private $m_expression = "";
    private $m_result = "";
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function serialize($_code = "calculator") {
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->addData($_code, "expression", utf8_to_b64($this->m_expression));
        $lDom->addData($_code, "result", $this->m_result);
        return $lDom->toString();
    }
    //===============================================
    public function deserialize($_data, $_code = "calculator") {
        parent::deserialize($_data);
        $lDom = new GCode();
        $lDom->loadXml($_data);
        $this->m_expression = b64_to_utf8($lDom->getData($_code, "expression"));
        $this->m_result = $lDom->getData($_code, "result");
    }
    //===============================================
    public function run($_data) {
        $this->deserialize($_data);
        if($this->m_method == "") {
            $this->m_logs->addError("Le module est obligatoire.");
        }
        else if($this->m_method == "run_calculator") {
            $this->onRunCalculator($_data);
        }
        else {
            $this->m_logs->addError("Le module est inconnu.");
        }
    }
    //===============================================
    public function onRunCalculator($_data) {
        if($this->m_expression == "") {
            $this->m_logs->addError("L'expression est vide.");
            return;
        }
    }
    //===============================================
}
?>
