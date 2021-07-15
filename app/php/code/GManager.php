<?php
class GManager {
    //===============================================
    private static $instance = null;
    //===============================================
    public function __construct() {
        // manager
        $this->mgr = new sGManager();
        // app
        $this->mgr->app = new sGApp();
        $this->mgr->app->app_name = "ReadyApp";
        $this->mgr->app->debug_file = "debug.txt";
        $this->mgr->app->tmp_dir = "tmp";
        $this->mgr->app->tmp_upload_file = "tmp/tmp_upload_file.tmp";
    }
    //===============================================
    public static function Instance() {
        if(is_null(self::$instance)) {
            self::$instance = new GManager();  
        }
        return self::$instance;
    }
    //===============================================
    public function startSession() {
        session_start();
    }
    //===============================================
    public function postRedirectGet() {
        $lApp = $this->mgr->app;
        if(!empty($_POST) OR !empty($_FILES)) {
            $_SESSION["save_post"] = $_POST ;
            $_SESSION["save_files"] = $_FILES ;
            
            $lUrl = $_SERVER["PHP_SELF"] ;
            
            if(!empty($_SERVER["QUERY_STRING"])) {
                $lUrl .= "?" . $_SERVER["QUERY_STRING"] ;
            }
            
            if(!empty($_FILES)) {
                $this->createDir($lApp->tmp_dir);
                foreach($_FILES as $lKey => $lValue) {
                    move_uploaded_file($_FILES[$lKey]["tmp_name"], $lApp->tmp_upload_file);
                }
            }
            
            header("Location: " . $lUrl);
            exit;
        }
           
        if(isset($_SESSION["save_post"])) {
            $_POST = $_SESSION["save_post"] ;
            $_FILES = $_SESSION["save_files"] ;
            unset($_SESSION["save_post"], $_SESSION["save_files"]);
        }
    }
    //===============================================
    public function createDir($path) {
        if(!file_exists($path)) {
            mkdir($path, 0777, true);
        }
    }
    //===============================================
    public function moveUploadFile($file) {
        $lApp = $this->mgr->app;
        $lCopyFlag = copy($lApp->tmp_upload_file, $file);
        unlink($lApp->tmp_upload_file);
        return $lCopyFlag;
    }
    //===============================================
    public function write($data) {
        $lApp = $this->mgr->app;
        $lFile = fopen($lApp->debug_file, "a+");
        fwrite($lFile, $data . "\n");
        fclose($lFile);
    }
    //===============================================
}
//===============================================
class sGManager {
    public $app;
}
//===============================================
class sGApp {
    // app
    public $app_name;
    // debug
    public $debug_file;
    // tmp
    public $tmp_dir;
    public $tmp_upload_file;
}
//===============================================
?>
