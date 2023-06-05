//===============================================
#ifndef _GCalculator_
#define _GCalculator_
//===============================================
#include "GManager.h"
//===============================================
class GCalculator : public GManager {
public:
    GCalculator();
    ~GCalculator();
    GString serialize(const GString& _code = "calculator") const;
    void deserialize(const GString& _data, const GString& _code = "calculator");
    void run(const GString& _data);
    void onRunCalculator(const GString& _data);

protected:
    GString m_expression;
    GString m_result;
};
//===============================================
#endif
//===============================================
