<?php   
//===============================================
class GLog {
    //===============================================
    private $m_type;
    private $m_msg;
    private $m_map = array();
    //===============================================
    public function __construct() {

    }
    //===============================================
    public function clone() {
        return new GLog();
    }
    //===============================================
    public function setObj($_obj) {
        $this->m_type = $_obj->m_type;
        $this->m_msg = $_obj->m_msg;
    }
    //===============================================
    public function size() {
        return count($this->m_map);
    }
    //===============================================
    public function clearMap() {
        $this->m_map = array();
    }
    //===============================================
    public function addError($_msg) {
        $lObj = new GLog();
        $lObj->m_type = "error";
        $lObj->m_msg = $_msg;
        $this->m_map[] = $lObj;
    }
    //===============================================
    public function addLog($_msg) {
        $lObj = new GLog();
        $lObj->m_type = "log";
        $lObj->m_msg = $_msg;
        $this->m_map[] = $lObj;
    }
    //===============================================
    public function addData($_msg) {
        $lObj = new GLog();
        $lObj->m_type = "data";
        $lObj->m_msg = $_msg;
        $this->m_map[] = $lObj;
    }
    //===============================================
    public function addLogs($_obj) {
        for($i = 0; $i < $_obj->size(); $i++) {
            $lObj = $_obj->m_map[$i];
            $lNew = $this->clone();
            $lNew->setObj($lObj);
            $this->m_map[] = $lNew;
        }
    }
    //===============================================
    public function loadToMap($_index) {
        if($_index >= 1 && $_index <= $this->size()) {
            $lObj = $this->m_map[$_index - 1];
            $lObj->setObj($this);
        }
    }
    //===============================================
    public function loadFromMap($_index) {
        if($_index >= 1 && $_index <= $this->size()) {
            $lObj = $this->m_map[$_index - 1];
            $this->setObj($lObj);
        }
    }
    //===============================================
    public function showLogs() {
        if(!$this->size()) return;
        echo sprintf("<div id='LogsPhp' hidden>%s</div>\n", $this->serialize());
        echo sprintf("<script>call_server('logs', 'show_php_logs');</script>\n");
    }
    //===============================================
    public function showLogsA() {
        for($i = 0; $i < $this->size(); $i++) {
            $lObj = $this->m_map[$i];
            echo sprintf("[%s] : %s<br>\n", $lObj->m_type, $lObj->m_msg);
        }
    }
    //===============================================
    public function serialize($_code = "logs") {
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->addData($_code, "type", $this->m_type);
        $lDom->addData($_code, "msg", utf8_to_b64($this->m_msg));
        $lDom->addMap($_code, $this->m_map);
        return $lDom->toString();
    }
    //===============================================
    public function deserialize($_data, $_code = "logs") {
        $lDom = new GCode();
        $lDom->loadXml($_data);
        $this->m_type = $lDom->getData($_code, "type");
        $this->m_msg = b64_to_utf8($lDom->getData($_code, "msg"));
        $lDom->getMap($_code, $this->m_map, $this);
    }
    //===============================================
 }
//===============================================
?>
