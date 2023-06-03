<?php   
//===============================================
class GManager extends GObject {
    //===============================================
    protected $m_module = "";
    protected $m_method = "";
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function serialize($_code = "manager") {
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->addData($_code, "module", $this->m_module);
        $lDom->addData($_code, "method", $this->m_method);
        return $lDom->toString();
    }
    //===============================================
    public function deserialize($_data, $_code = "manager") {
        $lDom = new GCode();
        $lDom->loadXml($_data);
        $this->m_module = $lDom->getData($_code, "module");
        $this->m_method = $lDom->getData($_code, "method");
    }
    //===============================================
 }
//===============================================
?>
