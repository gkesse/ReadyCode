<?php   
//===============================================
class GTest extends GObject {
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function run($_module, $_method) {
        if($_method == "xml") {
            $this->runXml($_module, $_method);
        }
        else if($_method == "code") {
            $this->runCode($_module, $_method);
        }
        else if($_method == "log") {
            $this->runLog($_module, $_method);
        }
        else if($_method == "curl_client") {
            $this->runCurlClient($_module, $_method);
        }
        else if($_method == "socket_client") {
            $this->runSocketClient($_module, $_method);
        }
    }
    //===============================================
    public function runJs($_module, $_method) {
        echo sprintf("runJs...<br>\n");
        echo sprintf("<script>call_server('test', '%s');</script>\n", $_method);
    }
    //===============================================
    public function runXml($_module, $_method) {
        echo sprintf("runXml...<br>\n");
        $lDom = new GXml();
        $lDomC1 = new GXml();
        $lDomC2 = new GXml();
        
        // createDoc - setNode - addObj - addData - toString
        $lDom->createDoc();
        $lDomC1->setNode($lDom->addObj($lDom, "datas"));
        $lDomC2->setNode($lDomC1->addObj($lDom, "data"));
        $lDomC2->setNode($lDomC2->addData($lDom, "code", "logs"));
        $lDomC2->setNode($lDomC2->addData($lDom, "type", "error"));
        $lDomC2->setNode($lDomC2->addData($lDom, "msg", "La connexion a échoué."));
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // createNode
        $lDom->createDoc();
        $lDomC1->setNode($lDom->createNode($lDom, "/rdv/datas/data"));
        $lDomC1->setNode($lDom->createNode($lDom, "/rdv/datas/data"));
        $lDomC2->setNode($lDomC1->createNode($lDom, "rdv/datas/data"));
        $lDomC2->setNode($lDomC1->createNode($lDom, "rdv/datas/data"));
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // loadXml
        $lDom->loadXml($lDom->toString());
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // loadXml
        $lData = "";
        $lData .= "<rdv>";
        $lData .= "<datas>";
        $lData .= "<data>";
        $lData .= "<code>logs</code>";
        $lData .= "<type>error</type>";
        $lData .= "<msg>La connexion a échoué.</msg>";
        $lData .= "</data>";
        $lData .= "</datas>";
        $lData .= "</rdv>";
        $lDom->loadXml($lData);
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // toNode
        $lDom->createDoc();
        $lDomC1->setNode($lDom->addObj($lDom, "datas"));
        $lDomC2->setNode($lDomC1->addObj($lDom, "data"));
        $lDomC2->setNode($lDomC2->addData($lDom, "code", "logs"));
        $lDomC2->setNode($lDomC2->addData($lDom, "type", "error"));
        $lDomC2->setNode($lDomC2->addData($lDom, "msg", "La connexion a échoué."));
        echo sprintf("<xmp>%s</xmp>\n", $lDomC1->toNode($lDom));
        
        // loadNode
        $lData = "";
        $lData .= "<datas>";
        $lData .= "<data>";
        $lData .= "<code>logs</code>";
        $lData .= "<type>error</type>";
        $lData .= "<msg>La connexion a échoué.</msg>";
        $lData .= "</data>";
        $lData .= "</datas>";
        $lDom->createDoc();
        $lDomC1->setNode($lDom->createNode($lDom, "/rdv/datas"));
        $lDomC1->loadNode($lDom, $lData);
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
    }
    //===============================================
    public function runCode($_module, $_method) {
        echo sprintf("runCode...<br>\n");
        
        // createDoc - createDatas
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->createDatas();
        $lDom->createDatas();
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // createCode
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->createCode("logs");
        $lDom->createCode("logs");
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // serialize
        $lLog = new GLog();
        $lLog->addError("Le serveur n'est pas disponible.");
        $lLog->addData("La taille de la fenêtre est: 1000.");
        $lLog->addLog("Le chargement du module est terminé.");
        $lLog->loadFromMap(3);
        echo sprintf("<xmp>%s</xmp>\n", $lLog->serialize());
        
        // addData - toDatas
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->addData("manager", "module", "logs");
        $lDom->addData("manager", "method", "load_logs");
        $lDom->addData("manager", "module", "logs_2");
        $lDom->addData("manager", "method", "load_logs_2");
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // loadData
        $lDom = new GCode();
        $lDom->createDoc();
        $lDom->addData("manager", "module", "logs");
        $lDom->addData("manager", "method", "load_logs");
        $lDom->loadData($lLog->serialize());
        echo sprintf("<xmp>%s</xmp>\n", $lDom->toString());
        
        // deserialize
        $lLog2 = new GLog();
        $lLog2->deserialize($lLog->serialize());
        echo sprintf("<xmp>%s</xmp>\n", $lLog2->serialize());
        
    }
    //===============================================
    public function runLog($_module, $_method) {
        echo sprintf("runLog...<br>\n");
        
        // addError - addData - addLog - addLogs
        $lLog = new GLog();
        $lLog->addError("Le serveur n'est pas disponible.");
        $lLog->addData("La taille de la fenêtre est: 1000.");
        $lLog->addLog("Le chargement du module est terminé.");
        $this->m_logs->addLogs($lLog);
    }
    //===============================================
    public function runCurlClient($_module, $_method) {
        echo sprintf("runCurlClient...<br>\n");
    }
    //===============================================
    public function runSocketClient($_module, $_method) {
        echo sprintf("runSocketClient...<br>\n");
        
        // callFacade
        $lClient = new GSocket();
        $lData = $lClient->callFacade("logs", "save_logs");
        $this->m_logs->deserialize($lData);
        $this->m_logs->addLogs($lClient->getLogs());
    }
    //===============================================
 }
//===============================================
?>
