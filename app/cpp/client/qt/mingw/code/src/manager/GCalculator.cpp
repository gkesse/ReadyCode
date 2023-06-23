//===============================================
#include "GCalculator.h"
#include "GSocket.h"
//===============================================
GCalculator::GCalculator()
: GFacade() {

}
//===============================================
GCalculator::~GCalculator() {

}
//===============================================
void GCalculator::setExpression(const GString& _expression) {
    m_expression = _expression;
}
//===============================================
void GCalculator::setResult(const GString& _result) {
    m_result = _result;
}
//===============================================
GString GCalculator::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "expression", m_expression.toBase64());
    lDom.addData(_code, "result", m_result);
    lDom.loadData(GFacade::serialize());
    return lDom.toString();
}
//===============================================
void GCalculator::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_expression = lDom.getData(_code, "expression").fromBase64();
    m_result = lDom.getData(_code, "result");
}
//===============================================
void GCalculator::runCalculator() {
    GString lData = serialize();
    lData.print();
    GSocket lClient;
    lData = lClient.callFacade("calculator", "run_calculator", lData);
    deserialize(lData);
    m_logs.deserialize(lData);
}
//===============================================
