<?php
class GCalculator extends GManager {
    //===============================================
    private $m_expression = "";
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function serialize($_code = "calculator") {
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->addData($_code, "expression", $this->m_expression);
        return $lDom->toString();
    }
    //===============================================
    public function deserialize($_data, $_code = "calculator") {
        parent::deserialize($_data);
        $lDom = new GCode();
        $lDom->loadXml($_data);
        $this->m_expression = $lDom->getData($_code, "expression");
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
        //$this->m_logs->addData("Bonjour tout le monde");
    }
    //===============================================
}
?>
