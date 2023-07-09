<?php   
//===============================================
class GObject {
    //===============================================
    protected $m_logs = null;
    protected $m_resp = null;
    //===============================================
    public function __construct() {
        $this->m_logs = new GLog();
        $this->m_resp = new GCode();
        $this->m_resp->createDoc();
    }
    //===============================================
    public function clearMap() {
        $this->m_map = array();
    }
    //===============================================
    public function getLogs() {
        return $this->m_logs;
    }
    //===============================================
    public function getResponse() {
        return $this->m_resp->toString();
    }
    //===============================================
 }
//===============================================
?>
