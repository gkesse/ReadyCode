//===============================================
package manager;
//===============================================
class GProcess {  
    public GProcess() {  

    }  
    //===============================================
    public void run(String[] _args) {
        String lModule = "test";
        if(args.length > 0) lKey = args[0];
        if(lKey.equals("test")) {runTest(args); return;}
        if(lKey.equals("ui")) {runUi(args); return;}
        runTest(args); 
    }        
    //===============================================
}
//===============================================
