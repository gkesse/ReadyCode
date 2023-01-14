//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
class GObject;
class GLog;
class GJson;
//===============================================
class GCode : public GXml {
public:
    GCode();
    ~GCode();

    bool createCode();
    bool createCode(const GString& _code);
    bool createRequest(const GString& _modules, const GString& _method);

    bool loadData(const GString& _data);

    bool getCode();
    bool getCode(const GString& _code);
    bool getCode(const GString& _code, const GString& _key);
    bool getMap(const GString& _code, int _index);

    GString getData(const GString& _code, const GString& _key);
    bool getData(const GString& _code, std::vector<GObject*>& _map, GObject* _obj);
    bool getData(const GString& _code, std::vector<GLog*>& _map, GLog* _obj);

    bool addData(const GString& _code, const GString& _key, const GString& _value , bool _isCData = false);
    bool addData(const GString& _code, const std::vector<GObject*>& _map);
    bool addData(const GString& _code, const std::vector<GLog*>& _map);
    bool addData(const GString& _data);

    void clearMap(std::vector<GObject*>& _map);
    int countMap(const GString& _code);
    bool hasCode();

    GString toData();
    GString toJson();
    void toJson(xmlNodePtr _node, int& _state, GString& _data, GJson& _json);
};
//==============================================
#endif
//==============================================
