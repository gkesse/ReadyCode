<?php   
//===============================================
class GSocket extends GObject {
    //===============================================
    private $m_socket = null;
    //===============================================
    public function __construct() {
        parent::__construct();
    }
    //===============================================
    public function sendData($_data) {
        fwrite($this->m_socket, $_data, strlen($_data));
    }
    //===============================================
    public function readData() {
        $lLength = 1024;
        $lData = "";
        while(1) {
            $lBuffer = fread ($this->m_socket, $lLength);
            if($lBuffer == "") break;
            $lData .= $lBuffer;
            $lStatus = socket_get_status($this->m_socket);
            $lBytes = $lStatus["unread_bytes"];
            if($lBytes <= 0) break;
        }
        return $lData;
    }
    //===============================================
    public function callServer($_data) {
        $lHostname = "127.0.0.1";
        $lPort = 8002;
        
        $lAddress = sprintf("tcp://%s:%d", $lHostname, $lPort);
        $lErrno = null;
        $lErrstr = null;
        
        $this->m_socket = stream_socket_client($lAddress, $lErrno, $lErrstr, 30);

        if(!$this->m_socket) {
            $this->m_logs->addError("La connexion au serveur a échoué.");
            return;
        }
        
        $this->sendData($_data);
        $lData = $this->readData();

        fclose($this->m_socket);
        return $lData;
    }
    //===============================================
 }
//===============================================
?>
