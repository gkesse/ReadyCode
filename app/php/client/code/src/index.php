<?php
//===============================================
require "./php/class/GAutoload.php";
require "./php/functions.php";
//===============================================
$lProcess = new GProcess();
$lProcess->toHeader();
$lProcess->run("test", "socket_client");
$lProcess->toFooter();
$lProcess->getLogs()->showLogs();
//===============================================
?>