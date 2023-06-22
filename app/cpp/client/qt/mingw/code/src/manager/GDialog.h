//===============================================
#ifndef _GDialog_
#define _GDialog_
//===============================================
#include "GInclude.h"
#include "GLog.h"
//===============================================
class GDialog : public QDialog {
    Q_OBJECT

public:
    GDialog(QWidget* _parent = 0);
    virtual ~GDialog();
    virtual GDialog* clone();
    virtual void clear();
    virtual void setObj(const GDialog& _obj);
    virtual GDialog& loadFromMap(int i);
    virtual GDialog& loadToMap(int i);
    virtual bool isEqual(const GDialog& _obj) const;
    virtual int indexOf(const GDialog& _obj) const;
    virtual int size() const;
    void print() const;
    virtual GString serialize(const GString& _code = "forms") const;
    virtual void deserialize(const GString& _data, const GString& _code = "forms");

protected:
    GLog m_logs;
    std::vector<GDialog*> m_map;
};
//===============================================
#endif
//===============================================
