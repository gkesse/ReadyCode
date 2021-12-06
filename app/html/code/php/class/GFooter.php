<?php   
//===============================================
class GFooter extends GWidget {
    //===============================================
    private static $m_instance = null;
    //===============================================
    protected $dom;
    //===============================================
    public function __construct() {
        parent::__construct();
        $this->dom = new GDomXml();
        $this->dom->createDom();
        $this->dom->loadXmlFile("footer.xml");
    }
    //===============================================
    public static function Instance() {
        if(is_null(self::$m_instance)) {
            self::$m_instance = new GFooter();  
        }
        return self::$m_instance;
    }
    //===============================================
    public function show() {
        echo sprintf("</body>\n");
        echo sprintf("</html>\n");
    }
    //===============================================
}
//===============================================
?>
