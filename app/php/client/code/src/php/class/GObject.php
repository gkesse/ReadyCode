<?php   
//===============================================
class GObject {
    //===============================================
    protected $m_logs = null;
    protected $m_response = null;
    //===============================================
    public function __construct() {
        $this->m_logs = new GLog();
        $this->m_response = new GCode();
        $this->m_response->createDoc();
        $this->m_response->createDatas();
    }
    //===============================================
    public function getLogs() {
        return $this->m_logs;
    }
    //===============================================
    public function getResponse() {
        return $this->m_response->toString();
    }
    //===============================================
 }
//===============================================
?>
