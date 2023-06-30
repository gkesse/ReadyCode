//===============================================
#include "GCalculator.h"
#include "GSocket.h"
//===============================================
GCalculator::GCalculator()
: GFacade() {

}
//===============================================
GCalculator::~GCalculator() {
    clearMap();
}
//===============================================
GObject* GCalculator::clone() const {
    return new GCalculator;
}
//===============================================
void GCalculator::setObj(const GObject& _obj) {
    const GCalculator& lObj = dynamic_cast<const GCalculator&>(_obj);
    m_expression = lObj.m_expression;
    m_result = lObj.m_result;
}
//===============================================
void GCalculator::addObj(const GCalculator& _obj) {
    GCalculator* lObj = new GCalculator;
    lObj->setObj(_obj);
    m_map.push_back(lObj);
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
const GString& GCalculator::getExpression() const {
    return m_expression;
}
//===============================================
const GString& GCalculator::getResult() const {
    return m_result;
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
    GSocket lClient;
    lData = lClient.callFacade("calculator", "run_calculator", lData);
    m_logs.addLogs(lClient.getLogs());
    m_logs.deserialize(lData);
    deserialize(lData);
}
//===============================================
