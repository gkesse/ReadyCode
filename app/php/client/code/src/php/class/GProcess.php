<?php   
//===============================================
class GProcess extends GObject {
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function toHeader() {
        echo sprintf("<!DOCTYPE html>\n");
        echo sprintf("<html lang='fr'>\n");
        echo sprintf("<head>\n");
        // title
        echo sprintf("<title>ReadyApp</title>\n");
        // charset
        echo sprintf("<meta charset='UTF-8'/>\n");
        // viewport
        echo sprintf("<meta name='viewport' content='width=device-width, maximum-scale=1.0, minimum-scale=1.0, initial-scale=1.0, user-scalable=no'/>\n");
        // styles.css
        $this->toCss();
        // scripts
        $this->toScripts();
        //
        echo sprintf("</head>\n");
        echo sprintf("<body class='Body1'>\n");
        //
        $this->toLog();
    }
    //===============================================
    public function toLog() {
        echo sprintf("<div class='Log1' id='LogModal'>\n");
        echo sprintf("<div class='Log2' id='LogForm'>\n");
        // close
        echo sprintf("<div class='Log3' onclick='call_server(\"logs\", \"close_logs\", this)'>\n");
        echo sprintf("<i class='fa fa-times'></i></div>\n");
        // title
        echo sprintf("<div class='Log4' id='LogTitle'>Logs</div>\n");
        //
        echo sprintf("<div class='Log5'>\n");
        // intro
        echo sprintf("<div class='Log6' id='LogIntro'>Consultez les logs.</div>\n");
        //
        echo sprintf("<div class='Log7'>\n");
        // body
        echo sprintf("<div id='LogBody'></div>\n");
        //
        echo sprintf("</div>\n");
        echo sprintf("<div class='Log8'>\n");
        // ok
        echo sprintf("<div class='Log9' onclick='call_server(\"logs\", \"close_logs\", this)'>OK</div>\n");
        //
        echo sprintf("</div>\n");
        echo sprintf("</div>\n");
        echo sprintf("</div>\n");
        echo sprintf("</div>\n");
    }
    //===============================================
    public function toFooter() {
        echo sprintf("</body>\n");
        echo sprintf("</html>\n");
    }
    //===============================================
    public function toCss() {
        // icon
        echo sprintf("<link rel='icon' href='./data/site/logo.png' type='image/png'>\n");
        // font-awesome
        echo sprintf("<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>\n");
        // fonts.googleapis.com
        echo sprintf("<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Anton'>\n");
        // style.css
        echo sprintf("<link rel='stylesheet' href='./css/styles.css'>\n");
    }
    //===============================================
    public function toScripts() {
        // scripts.js
        echo sprintf("<script src='./js/functions.js'></script>\n");
        echo sprintf("<script src='./js/class/GXml.js'></script>\n");
        echo sprintf("<script src='./js/class/GLog.js'></script>\n");
        echo sprintf("<script src='./js/class/GObject.js'></script>\n");
        echo sprintf("<script src='./js/class/GTest.js'></script>\n");
        echo sprintf("<script src='./js/class/GServer.js'></script>\n");
        echo sprintf("<script src='./js/scripts.js'></script>\n");
    }
    //===============================================
    public function run($_module, $_method) {
        if($_module == "") {
            $this->m_logs->addError("Le module est obligatoire.");
        }
        else if($_module == "test") {
            $this->runTest($_module, $_method);
        }
        else if($_module == "test_js") {
            $this->runTestJs($_module, $_method);
        }
        else if($_module == "client") {
            $this->runClient($_module, $_method);
        }
        else {
            $this->m_logs->addError("Le module est inconnu.");
        }
    }
    //===============================================
    public function runTest($_module, $_method) {
        $lObj = new GTest();
        $lObj->run($_module, $_method);
        $this->m_logs->addLogs($lObj->m_logs);
    }
    //===============================================
    public function runTestJs($_module, $_method) {
        $lObj = new GTest();
        $lObj->runJs($_module, $_method);
        $this->m_logs->addLogs($lObj->m_logs);
    }
    //===============================================
    public function runClient($_module, $_method) {

    }
    //===============================================
 }
//===============================================
?>
