<?php
//===============================================
require "./php/class/GAutoload.php";
//===============================================
$lProcess = new GProcess();
$lProcess->toHeader();
$lProcess->run("test_js", "xml");
$lProcess->toFooter();
$lProcess->getLogs()->showLogs();
//===============================================
?>