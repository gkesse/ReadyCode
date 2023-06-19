<?php
    session_start();
    //===============================================
    function GAutoloadRegister($_classname) {
        $m_filename = dirname(__FILE__).DIRECTORY_SEPARATOR.$_classname.".php";

        if (is_readable($m_filename)) {
            require $m_filename;
        }    
    }       
    //===============================================
    if (version_compare(PHP_VERSION, "5.1.2", ">=")) {
        if (version_compare(PHP_VERSION, "5.3.0", ">=")) {
            spl_autoload_register("GAutoloadRegister", true, true);
        } 
        else {
            spl_autoload_register("GAutoloadRegister");
        }
    } 
    else {
        function spl_autoload_register($class_name) {
            include $class_name.".php";
        }       
    }
    //===============================================
?>
