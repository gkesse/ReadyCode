<?php   
//===============================================
class GServer extends GManager {
    //===============================================
    private $m_type = "";
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function sendResponse() {
        $this->m_response->loadData($this->m_logs->serialize());
        $lData = $this->m_response->toString();
        echo $lData;
    }
    //===============================================
    public function serialize($_code = "server") {
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->addData($_code, "type", $this->m_type);
        return $lDom->toString();
    }
    //===============================================
    public function deserialize($_data, $_code = "server") {
        $lDom = new GCode();
        $lDom->loadXml($_data);
        $this->m_type = $lDom->getData($_code, "type");
    }
    //===============================================
    public function run($_data) {
        $this->deserialize($_data);
        if($this->m_type == "") {
            $this->m_logs->addError("Le type du serveur est obligatoire.");
        }
        else if($this->m_type == "local") {
            $this->runLocal($_data);
        }
        else if($this->m_type == "remote") {
            $this->runRemote($_data);
        }
        else {
            $this->m_logs->addError("Le type du serveur est inconnu.");
        }
    }
    //===============================================
    public function runLocal($_data) {
        $lObj = new GLocal();
        $lObj->run($_data);
        $this->m_logs->addLogs($lObj->getLogs());
        $this->m_response->loadData($lObj->getResponse());
    }
    //===============================================
    public function runRemote($_data) {

    }
    //===============================================
 }
//===============================================
?>
