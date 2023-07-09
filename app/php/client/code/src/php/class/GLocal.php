<?php
class GLocal extends GManager {
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function run($_data) {
        parent::deserialize($_data);
        if($this->m_module == "") {
            $this->m_logs->addError("Le module est obligatoire.");
        }
        else if($this->m_module == "calculator") {
            $this->runCalculator($_data);
        }
        else {
            $this->m_logs->addError("Le module est inconnu.");
        }
    }
    //===============================================
    public function runCalculator($_data) {
        $lObj = new GCalculator();
        $lObj->run($_data);
        $this->m_logs->addLogs($lObj->getLogs());
        $this->m_resp->loadData($lObj->serialize());
    }
    //===============================================
}
?>
