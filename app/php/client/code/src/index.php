<?php
//===============================================
require $_SERVER["DOCUMENT_ROOT"]."/php/class/GInclude.php";
//===============================================
$lProcess = new GProcess();
$lProcess->toHeader();
$lProcess->run("window", "calculator");
$lProcess->toFooter();
$lProcess->getLogs()->showLogs();
//===============================================
?>