//===============================================
#ifndef _GDateTime_
#define _GDateTime_
//===============================================
#include "GObject.h"
//===============================================
class GDateTime : public jed_utils::datetime {
public:
    GDateTime();
    GDateTime(const datetime& _obj);
    GDateTime(datetime&& _obj) noexcept;
    GDateTime(const GDateTime& _obj);
    ~GDateTime();
    bool isEmpty() const;
    bool toParse(const GString& _data);
    GString toString() const;

private:
    bool m_isEmpty;
};
//===============================================
#endif
//===============================================
