//===============================================
import manager.GProcess;
//===============================================
class GMain {  
    public static void main(String[] _args) {
        GProcess lProcess = new GProcess();
        lProcess.run(_args);
        lProcess.getLogs().showLogsX();
    }
}
//===============================================
