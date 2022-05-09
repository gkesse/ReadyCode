//===============================================
class GSocket {
    //===============================================
    constructor() {
        this.address_ip = "127.0.0.1";
        this.port = 8900;
        this.protocol = "ws";
        this.updateUrl();
    }
    //===============================================
    setAddressIp(_addressIp) {
        this.address_ip = _addressIp;
        this.updateUrl();
    }
    //===============================================
    setPort(_port) {
        this.port = _port;
        this.updateUrl();
    }
    //===============================================
    updateUrl() {
        this.url = "ws://" + this.address_ip + ":" + this.port;
        alert(this.url);
    }
    //===============================================
    openSocket() {
        var lWebSocket = new WebSocket(this.url, this.protocol);
        lWebSocket.onopen = function() {
            console.log("open sesame");
        }
        lWebSocket.onclose = function() {
            console.log("close sesame");
        }
        lWebSocket.onerror = ohno;
        lWebSocket.onmessage = function(e) {
            var msg = e.data;
            alert(msg);
        }
    }
    //===============================================
}
//===============================================
