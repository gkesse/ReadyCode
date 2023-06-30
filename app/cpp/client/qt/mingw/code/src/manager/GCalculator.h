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
    GObject* clone() const;
    void setObj(const GObject& _obj);
    void addObj(const GCalculator& _obj);
    void setExpression(const GString& _expression);
    void setResult(const GString& _result);
    const GString& getExpression() const;
    const GString& getResult() const;
    GString serialize(const GString& _code = "calculator") const;
    void deserialize(const GString& _data, const GString& _code = "calculator");
    void runCalculator();

private:
    GString m_expression;
    GString m_result;
};
//===============================================
#endif
//===============================================
