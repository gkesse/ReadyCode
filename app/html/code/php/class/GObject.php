<?php   
//===============================================
class GObject {
    //===============================================
    protected $dataRoot;
    //===============================================
    public function __construct() {
        $this->dataRoot = "data";
    }
    //===============================================
    public function setDataRoot($root) {
        $this->dataRoot = $root;
    }
    //===============================================
    public function getDataPath($repo, $file) {
        $lPath = sprintf("%s/%s/%s/%s", $_SERVER["DOCUMENT_ROOT"], $this->dataRoot, $repo, $file);
        if(!file_exists($lPath)) {
            GError::Instance()->addError(sprintf("Error le fichier n'existe pas : %s", $lPath));
            return "";
        }
        return $lPath;
    }
    //===============================================
}
//===============================================
?>
