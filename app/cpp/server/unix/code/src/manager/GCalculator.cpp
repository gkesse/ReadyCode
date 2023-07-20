//===============================================
#include "GCalculator.h"
//===============================================
GCalculator::GCalculator()
: GManager() {

}
//===============================================
GCalculator::~GCalculator() {

}
//===============================================
GString GCalculator::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "expression", m_expression.toBase64());
    lDom.addData(_code, "result", m_result);
    return lDom.toString();
}
//===============================================
void GCalculator::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_expression = lDom.getData(_code, "expression").fromBase64();
    m_result = lDom.getData(_code, "result");
}
//===============================================
void GCalculator::run(const GString& _data) {
    deserialize(_data);
    if(m_method == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_method == "run_calculator") {
        onRunCalculator(_data);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GCalculator::onRunCalculator(const GString& _data) {
    if(m_expression == "") {
        m_logs.addError("L'expression est obligatoire.");
        return;
    }

    double lResult = te_interp(m_expression.c_str(), 0);
    m_result = sformat("%.2f", lResult);
}
//===============================================
