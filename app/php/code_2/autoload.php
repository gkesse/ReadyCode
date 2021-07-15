<?php
//===============================================
spl_autoload_register(function($class_name) {
    $lFile = $class_name . ".php";
    require $lFile;
});
//===============================================
?>
