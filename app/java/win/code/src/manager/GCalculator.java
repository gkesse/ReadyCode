//===============================================
package manager;
//===============================================
import org.mariuszgromada.math.mxparser.Expression;
//===============================================
public class GCalculator extends GManager {  
    //===============================================
	String m_expression = "";
	String m_result = "";
    //===============================================
    public GCalculator() {  

    }  
    //===============================================
    public void setExpression(String _expression) {
    	m_expression = _expression;
    }
    //===============================================
    public void runCalculator() {
        GSocket lClient = new GSocket();
        String lData = serialize();
        lData = lClient.callFacade("calculator", "run_calculator", lData);
        m_logs.addLogs(lClient.getLogs());
        m_logs.deserialize(lData);
        deserialize(lData);
    }
    //===============================================
    public String serialize() {
        String lCode = "calculator";
        GCode lDom = new GCode();
        lDom.createDoc();
        lDom.addData(lCode, "expression", m_expression);
        lDom.addData(lCode, "result", m_result);
        return lDom.toString();
    }
    //===============================================
    public void deserialize(String _data) {
    	super.deserialize(_data);
        String lCode = "calculator";
        GCode lDom = new GCode();
        lDom.loadXml(_data);
        m_expression = lDom.getData(lCode, "expression");
        m_result = lDom.getData(lCode, "result");
    }
    //===============================================
    public void run(String _data) {
        deserialize(_data);
        if(m_method.equals("")) {
        	m_logs.addError("La méthode est obligatoire.");
        }
        else if(m_method.equals("run_calculator")) {
        	onRunCalculator(_data);
        }
        else {
        	m_logs.addError("La méthode est inconnue.");
        }
    }        
    //===============================================
    public void onRunCalculator(String _data) {
        if(m_expression.equals("")) {
        	m_logs.addError("L'expression est obligatoire.");
        	return;
        }
        
        Expression lExpression = new Expression(m_expression);
        Double lResult = lExpression.calculate();
        m_result = String.format("%.2f", lResult);
    }
    //===============================================
}
//===============================================
