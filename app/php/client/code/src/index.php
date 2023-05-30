<?php
//===============================================
require "./php/class/GAutoload.php";
//===============================================
$lProcess = new GProcess();
$lProcess->toHeader();
$lProcess->run("test_o", "xml");
$lProcess->toFooter();
$lProcess->getLogs()->showLogs();
//===============================================
?>