<?php
class GDatabase {
    //===============================================
    private static $instance = null;
    //===============================================
    public function __construct() {

    }
    //===============================================
    public static function Instance() {
        if(is_null(self::$instance)) {
            self::$instance = new GDatabase();  
        }
        return self::$instance;
    }
    //===============================================
    public function open() {
        echo sprintf("on ouvre la base de données<br/>\n");
    }
    //===============================================
    public function load() {
        echo sprintf("on charge la base de données<br/>\n");
    }
    //===============================================
    public function update() {
        echo sprintf("on modifie la base de données<br/>\n");
    }
    //===============================================
    public function save() {
        echo sprintf("on enregistre la base de données<br/>\n");
    }
    //===============================================
    public function close() {
        echo sprintf("on ferme la base de données<br/>\n");
    }
    //===============================================
}
?>
