<?php
//===============================================
require "autoload.php";
//===============================================
GManager::Instance()->startSession();
GManager::Instance()->postRedirectGet();
//===============================================
$lUploadFlag = false;
$lUploadDir = "uploads";
$lUploadFilename = "";
$lUploadFile = "";
$lUploadFileExt = "";
$lUploadFileExist = false;
$lUploadFileSize = 0;
$lUploadFileSizeValid = false;
$lUploadFileExtValid = false;
$lUploadValid = false;
//===============================================
$lUploadFileSizeMax = 2*1024*1024;
$lUploadFileExtMap = array("png", "bmp", "jpg", "jpeg", "gif");
//===============================================
if(!empty($_POST)) {
    $lUploadFlag = true;
    $lUploadFilename = basename($_FILES["upload_file"]["name"]);
    $lUploadFile = $lUploadDir . "/" . $lUploadFilename;
    $lUploadFileExt = strtolower(pathinfo($lUploadFile, PATHINFO_EXTENSION));
    $lUploadFileExist = file_exists($lUploadFile);
    $lUploadFileSize = $_FILES["upload_file"]["size"];
    $lUploadFileSizeValid = ($lUploadFileSize <= $lUploadFileSizeMax);
    $lUploadFileExtValid = in_array($lUploadFileExt, $lUploadFileExtMap);
    $lUploadValid = (!$lUploadFileExist && $lUploadFileSizeValid && $lUploadFileExtValid);
}
//===============================================
echo sprintf("<!DOCTYPE html>\n");
echo sprintf("<html lang='fr'>\n");
echo sprintf("<head>\n");
echo sprintf("<title>ReadyApp</title>\n");
echo sprintf("<link rel='stylesheet' href='style.css'>\n");
echo sprintf("</head>\n");
echo sprintf("<body>\n");

echo sprintf("<h1>Système d'hébergement de fichiers</h1>\n");

echo sprintf("<div><div class='border'>\n");
echo sprintf("<form action='' method='post' enctype='multipart/form-data'>\n");
echo sprintf("<input type='file' name='upload_file' required>\n");
echo sprintf("<input type='submit' value='Charger' name='upload'>\n");
echo sprintf("</form>\n");
echo sprintf("</div></div>\n");

if($lUploadFlag) {
    echo sprintf("<div><div class='border'>\n");
    echo sprintf("<div>lUploadFile : %s</div>\n", $lUploadFile);
    echo sprintf("<div>lUploadFileExt : %s</div>\n", $lUploadFileExt);
    echo sprintf("<div>lUploadFileExist : %d</div>\n", $lUploadFileExist);
    echo sprintf("<div>lUploadFileSize : %d</div>\n", $lUploadFileSize);
    echo sprintf("<div>lUploadFileSizeValid : %d</div>\n", $lUploadFileSizeValid);
    echo sprintf("<div>lUploadFileExtValid : %d</div>\n", $lUploadFileExtValid);
    echo sprintf("<div>lUploadValid : %d</div>\n", $lUploadValid);
    echo sprintf("</div></div>\n");

    if($lUploadValid) {
        GManager::Instance()->createDir($lUploadDir);
        
        $lMoveFlag = GManager::Instance()->moveUploadFile($lUploadFile);
        
        if($lMoveFlag) {
            echo sprintf("<div><div class='border'>\n");
            echo sprintf("<div>Le chargement du fichier a réussi</div>\n");
            echo sprintf("<div>Fichier : %s</div>\n", $lUploadFilename);
            echo sprintf("</div></div>\n");
        }
        else {
            echo sprintf("<div><div class='border'>\n");
            echo sprintf("<div>Le chargement du fichier a échoué</div>\n");
            echo sprintf("<div>Fichier : %s</div>\n", $lUploadFilename);
            echo sprintf("<div>Le fichier a peut-être un chemin invalide</div>\n");
            echo sprintf("</div></div>\n");
        }
    }
    else {
        echo sprintf("<div><div class='border'>\n");
        echo sprintf("<div>Le chargement du fichier a échoué</div>\n");
        echo sprintf("<div>Fichier : %s</div>\n", $lUploadFilename);
        echo sprintf("<div>Le fichier existe peut-être déjà</div>\n");
        echo sprintf("<div>Le fichier a peut-être une extension invalide</div>\n");
        echo sprintf("<div>Le fichier a peut-être une taille invalide</div>\n");
        echo sprintf("</div></div>\n");
    }
}

echo sprintf("</body>\n");
echo sprintf("</html>\n");
//===============================================
?>
