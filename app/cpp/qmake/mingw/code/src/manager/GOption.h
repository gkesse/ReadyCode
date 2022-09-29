//===============================================
#ifndef _GOption_
#define _GOption_
//===============================================
#include "GObject2.h"
//===============================================
class GOption : public GObject2 {
public:
    GOption();
    ~GOption();
    GObject2* clone() const;
    GString serialize(const GString& _code = "option") const;
    bool deserialize(const GString& _data, const GString& _code = "option");

    void setId(int _id);
    void setName(const GString& _name);
    void setState(bool _state);
    bool getState() const;
    std::vector<GObject2*>& getOptionMap();
    const std::vector<GObject2*>& getOptionMap() const;

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
    std::vector<GObject2*> m_map;
};
//==============================================
#endif
//==============================================
