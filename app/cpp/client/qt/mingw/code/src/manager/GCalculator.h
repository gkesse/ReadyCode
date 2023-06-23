//===============================================
#ifndef _GCalculator_
#define _GCalculator_
//===============================================
#include "GFacade.h"
//===============================================
class GCalculator : public GFacade {
public:
    GCalculator();
    ~GCalculator();
    void setExpression(const GString& _expression);
    void setResult(const GString& _result);
    GString serialize(const GString& _code = "calculator") const;
    void deserialize(const GString& _data, const GString& _code = "calculator");
    void runCalculator();

protected:
    GString m_expression;
    GString m_result;
};
//===============================================
#endif
//===============================================
