<?php   
//===============================================
class GHeader extends GWidget {
    //===============================================
    private static $m_instance = null;
    //===============================================
    protected $dom;
    //===============================================
    public function __construct() {
        parent::__construct();
        $this->dom = new GDomXml();
        $this->dom->createDom();
        $this->dom->loadXmlFile("header.xml");
    }
    //===============================================
    public static function Instance() {
        if(is_null(self::$m_instance)) {
            self::$m_instance = new GHeader();  
        }
        return self::$m_instance;
    }
    //===============================================
    public function show() {
        echo sprintf("<!DOCTYPE html>\n");
        echo sprintf("<html lang='%s'>\n", $this->getLang());
        echo sprintf("<head>\n");
        echo sprintf("<title>%s</title>\n", $this->geTitle());
        echo sprintf("<meta charset='UTF-8'/>\n");
        echo sprintf("<link rel='shortcut icon' type='image/png' href='%s'/>\n", $this->getLogo());
        echo sprintf("<meta http-equiv='X-UA-Compatible' content='IE=edge,chrome=1'/>\n");
        echo sprintf("<meta name='viewport' content='width=device-width, maximum-scale=1.0, minimum-scale=1.0, initial-scale=1.0, user-scalable=no'/>\n");
        echo sprintf("<link rel='stylesheet' href='/libs/font_awesome/css/font-awesome.min.css'/>\n");
        $this->loadFonts();
        echo sprintf("<link rel='stylesheet' href='/css/style.css'/>\n");
        $this->loadScripts();
        echo sprintf("</head>\n");
        echo sprintf("<body>\n");
    }
    //===============================================
    public function getLang() {
        $this->dom->getRoot("rdv")->getNode("header");
        $lLang = $this->dom->getNode("lang")->getValue();
        return $lLang;
    }
    //===============================================
    public function geTitle() {
        $this->dom->getRoot("rdv")->getNode("header");
        $lTitle = $this->dom->getNode("site")->getValue();
        return $lTitle;
    }
    //===============================================
    public function getLogo() {
        $this->dom->getRoot("rdv")->getNode("header");
        $lLogo = $this->dom->getNode("logo")->getValue();
        return $lLogo;
    }
    //===============================================
    public function loadFonts() {
        $this->dom->getRoot("rdv")->getNode("header");
        $lCount = $this->dom->getNode("fonts")->countNode();
        for($i = 0; $i < $lCount; $i++) {
            $this->dom->getNodeItem("font", $i);
            $lFont = $this->dom->getValue();
            echo sprintf("<link rel='stylesheet' href='%s'/>\n", $lFont);
        }
    }
    //===============================================
    public function loadScripts() {
        $this->dom->getRoot("rdv")->getNode("header");
        $lCount = $this->dom->getNode("scripts")->countNode();
        for($i = 0; $i < $lCount; $i++) {
            $this->dom->getNodeItem("script", $i);
            $lScript = $this->dom->getValue();
            echo sprintf("<script src='%s'></script>\n", $lScript);
        }
    }
    //===============================================
}
//===============================================
?>
