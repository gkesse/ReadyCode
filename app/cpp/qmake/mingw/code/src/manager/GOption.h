//===============================================
#ifndef _GOption_
#define _GOption_
//===============================================
#include "GObject.h"
//===============================================
class GOption : public GObject {
public:
    GOption();
    ~GOption();
    GObject* clone() const;
    GString serialize(const GString& _code = "option");
    bool deserialize(const GString& _data);

    void setId(int _id);
    void setName(const GString& _name);
    void setState(bool _state);
    bool getState() const;
    std::vector<GObject*>& getOptionMap();
    const std::vector<GObject*>& getOptionMap() const;

    void createOption();
    void enableOption();
    void disableOption();
    void readOption();
    void updateOption();
    void deleteOption();
    void searchOption();

private:
    int m_id;
    GString m_name;
    bool m_state;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
