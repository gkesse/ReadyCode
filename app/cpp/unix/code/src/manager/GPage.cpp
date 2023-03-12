//===============================================
#include "GPage.h"
#include "GMySQL.h"
//===============================================
GPage::GPage()
: GSearch() {
    m_id = 0;
    m_parentId = 0;
    m_typeId = 0;
    m_isDefault = false;
}
//===============================================
GPage::~GPage() {

}
//===============================================
GString GPage::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "parent_id", m_parentId);
    lDom.addData(_code, "type_id", m_typeId);
    lDom.addData(_code, "default", m_isDefault);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "type_name", m_typeName);
    lDom.addData(_code, "path", m_path);
    lDom.addData(_code, "id_path", m_idPath);
    lDom.addData(_code, "tree", m_tree.toBase64());
    lDom.addData(_code, "content", m_content.toBase64());
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
void GPage::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_parentId = lDom.getData(_code, "parent_id").toInt();
    m_typeId = lDom.getData(_code, "type_id").toInt();
    m_isDefault = lDom.getData(_code, "default").toBool();
    m_name = lDom.getData(_code, "name");
    m_typeName = lDom.getData(_code, "type_name");
    m_path = lDom.getData(_code, "path");
    m_idPath = lDom.getData(_code, "id_path");
    m_tree = lDom.getData(_code, "tree").fromBase64();
    m_content = lDom.getData(_code, "content").fromBase64();
    lDom.getData(_code, m_map, this);
}
//===============================================
GObject* GPage::clone() const {
    GPage* lObj = new GPage;
    lObj->setPage(*this);
    return lObj;
}
//===============================================
void GPage::setPage(const GPage& _obj) {
    m_id = _obj.m_id;
    m_parentId = _obj.m_parentId;
    m_typeId = _obj.m_typeId;
    m_isDefault = _obj.m_isDefault;
    m_name = _obj.m_name;
    m_typeName = _obj.m_typeName;
    m_path = _obj.m_path;
    m_idPath = _obj.m_idPath;
    m_tree = _obj.m_tree;
    m_content = _obj.m_content;
}
//===============================================
bool GPage::run(const GString& _request) {
    deserialize(_request);
    if(!m_parentId) m_parentId = 1;
    if(m_methodName == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_methodName == "save_page") {
        onSavePage();
    }
    else if(m_methodName == "save_page_file") {
        onSavePageFile();
    }
    else if(m_methodName == "load_page") {
        onLoadPage();
    }
    else if(m_methodName == "load_page_tree") {
        onLoadPageTree();
    }
    else if(m_methodName == "search_page") {
        onSearchPage();
    }
    else if(m_methodName == "search_page_file") {
        onSearchPageFile();
    }
    else if(m_methodName == "delete_page") {
        onDeletePage();
    }
    else {
        m_logs.addError("La méthode est inconnu.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onSavePage() {
    if(m_name.isEmpty()) {
        m_logs.addError("Le nom de la page est obligatoire.");
        return false;
    }
    if(!m_typeId) {
        m_logs.addError("Le type de la page est obligatoire.");
        return false;
    }
    if(!isParentDirectory()) {
        m_logs.addError("Le parent de la page est un fichier.");
        return false;
    }
    if(!m_id) {
        if(isRootFile()) {
            m_logs.addError("Vous essayez de créer un fichier à la racine.");
            return false;
        }
        if(isIndex()) {
            m_logs.addError("Le nom du fichier commence par index.");
            return false;
        }
        preparePath();
        insertPage();
        prepareIdPath();
    }
    else {
        if(!isTypeNoChange()) {
            m_logs.addError("Le type de la page a changé.");
            return false;
        }
        if(m_isDefault) {
            clearDefaultPage();
        }
        preparePath();
        updatePage();
        prepareIdPath();
    }
    if(!m_logs.hasErrors()) {
        m_logs.addLog("La donnée a bien été enregistrée.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onSavePageFile() {
    if(!m_id) {
        m_logs.addError("Aucune page n'a été sélectionnée.");
        return false;
    }
    if(!isFile()) {
        m_logs.addError("Vous devez sélectionné un fichier.");
        return false;
    }
    if(m_path.isEmpty()) {
        m_logs.addError("Le chemin de la page est obligatoire.");
        return false;
    }
    if(m_idPath.isEmpty()) {
        m_logs.addError("Le chemin des ids de la page est obligatoire.");
        return false;
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onLoadPage() {
    loadPage();
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onLoadPageTree() {
    loadPageTree(m_parentId);
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onSearchPage() {
    if(m_id != 0) {
        m_where += GFORMAT(" and t1._id = %d ", m_id);
    }
    else {
        if(m_parentId != 0) {
            m_where += GFORMAT(" and t1._parent_id = %d ", m_parentId);
        }
        if(!m_name.isEmpty()) {
            m_where += GFORMAT(" and t1._name like '%s%%' ", m_name.c_str());
        }
        if(m_typeId != 0) {
            m_where += GFORMAT(" and t1._type_id = %d ", m_typeId);
        }
    }
    searchPage();
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onSearchPageFile() {
    if(!m_id) {
        m_logs.addError("Aucune page n'a été sélectionnée.");
        return false;
    }
    if(!existPage()) {
        m_logs.addError("La page n'existe pas.");
        return false;
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onDeletePage() {
    if(!m_id) {
        m_logs.addError("Aucune page n'a été sélectionnée.");
        return false;
    }
    deletePage();
    if(!m_logs.hasErrors()) {
        m_logs.addLog("La donnée a bien été supprimée.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::isRoot() const {
    return (m_parentId == 1);
}
//===============================================
bool GPage::isFile() const {
    return (m_typeId == 1);
}
//===============================================
bool GPage::isDir() const {
    return (m_typeId == 2);
}
//===============================================
bool GPage::isRootFile() const {
    return (isRoot() && isFile());
}
//===============================================
bool GPage::isIndex() const {
    if(m_name.toLower().startBy("index")) return true;
    return false;
}
//===============================================
bool GPage::preparePath() {
    GMySQL lMySQL;
    GMySQL::GRows lDataRow = lMySQL.readRow(GFORMAT(""
            " select t1._path "
            " from _page t1 "
            " where 1 = 1"
            " and t1._id = %d "
            "", m_parentId
    ));
    m_logs.addLogs(lMySQL.getLogs());

    GPage lObj;
    int i = 0;

    lObj.m_path = lDataRow.at(i++);

    if(!m_logs.hasErrors()) {
        m_path = GFORMAT("%s/%s", lObj.m_path.c_str(), m_name.c_str());
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::prepareIdPath() {
    GMySQL lMySQL;
    GMySQL::GRows lDataRow = lMySQL.readRow(GFORMAT(""
            " select t1._id_path "
            " from _page t1 "
            " where 1 = 1"
            " and t1._id = %d "
            "", m_parentId
    ));
    m_logs.addLogs(lMySQL.getLogs());

    GPage lObj;
    int i = 0;

    lObj.m_idPath = lDataRow.at(i++);

    if(!m_logs.hasErrors()) {
        m_idPath = GFORMAT("%s/%d", lObj.m_idPath.c_str(), m_id);
        updateIdPath();
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::updateIdPath() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " update _page set "
            " _id_path = '%s' "
            " where 1 = 1 "
            " and _id = %d "
            "", m_idPath.c_str()
            , m_id
    ));
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::insertPage() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " insert into _page "
            " ( _parent_id, _type_id, _name, _path, _default ) "
            " values ( %d, %d, '%s', '%s', '%s' ) "
            "", m_parentId
            , m_typeId
            , m_name.c_str()
            , m_path.c_str()
            , GString(m_isDefault).c_str()
    ));
    m_logs.addLogs(lMySQL.getLogs());
    if(!m_logs.hasErrors()) {
        m_id = lMySQL.getId();
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::clearDefaultPage() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " update _page set "
            " _default = '0' "
            " where 1 = 1 "
            " and _parent_id = %d "
            " and _default = '1' "
            "", m_parentId
    ));
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::updatePage() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " update _page set "
            " _parent_id = %d "
            " , _type_id = %d "
            " , _default = '%s' "
            " , _name = '%s' "
            " , _path = '%s' "
            " , _id_path = '%s' "
            " where 1 = 1 "
            " and _id = %d "
            "", m_parentId
            , m_typeId
            , GString(m_isDefault).c_str()
            , m_name.c_str()
            , m_path.c_str()
            , m_idPath.c_str()
            , m_id
    ));
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::loadPage() {
    GMySQL lMySQL;
    GMySQL::GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select t1._id "
            " , t1._parent_id "
            " , t1._type_id "
            " , t1._default "
            " , t1._name "
            " , t1._path "
            " , t1._id_path "
            " , t2._name "
            " from _page t1 "
            " inner join _page_type t2 on 1 = 1 "
            " and t2._id = t1._type_id "
            " where 1 = 1 "
            " and t1._parent_id = %d "
            " and t1._type_id = 2 "
            " order by t1._name asc "
            "", m_parentId
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GMySQL::GRows lDataRow = lDataMap.at(i);
        int j = 0;
        GPage* lObj = new GPage;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_parentId = lDataRow.at(j++).toInt();
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_isDefault = lDataRow.at(j++).toBool();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_path = lDataRow.at(j++);
        lObj->m_idPath = lDataRow.at(j++);
        lObj->m_typeName = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::loadPageTree(int _parentId) {
    GMySQL lMySQL;
    GMySQL::GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select t1._id, t1._parent_id, t1._type_id, t1._default, t1._name, t2._name "
            " from _page t1 "
            " inner join _page_type t2 on 1 = 1 "
            " and t2._id = t1._type_id "
            " where 1 = 1 "
            " and t1._parent_id = %d "
            " order by t1._name asc "
            "", m_parentId
    ));

    if(lDataMap.size()) {
        GCode lDom;
        lDom.createCode("page");
        lDom.createXNode("map");

        for(int i = 0; i < (int)lDataMap.size(); i++) {
            GMySQL::GRows lDataRow = lDataMap.at(i);
            int j = 0;
            GPage lObj;
            lObj.m_id = lDataRow.at(j++).toInt();
            lObj.m_parentId = lDataRow.at(j++).toInt();
            lObj.m_typeId = lDataRow.at(j++).toInt();
            lObj.m_isDefault = lDataRow.at(j++).toBool();
            lObj.m_name = lDataRow.at(j++);
            lObj.m_typeName = lDataRow.at(j++);

            lDom.pushNode();
            GCode lData;
            lData.loadXml(lObj.serialize());
            lDom.loadNode(lData.toData());
            loadPageTree(lDom, lObj.m_id);
            lDom.popNode();
        }

        m_tree = lDom.toString();
    }

    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::loadPageTree(GCode& _dom, int _parentId) {
    GMySQL lMySQL(false);
    GMySQL::GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select t1._id "
            " , t1._parent_id "
            " , t1._type_id "
            " , t1._default "
            " , t1._name "
            " , t1._path "
            " , t1._id_path "
            " , t2._name "
            " from _page t1 "
            " inner join _page_type t2 on 1 = 1 "
            " and t2._id = t1._type_id "
            " where 1 = 1 "
            " and t1._parent_id = %d "
            " order by t1._name asc "
            "", _parentId
    ));

    if(lDataMap.size()) {
        _dom.last();
        _dom.createXNode("map");

        for(int i = 0; i < (int)lDataMap.size(); i++) {
            GMySQL::GRows lDataRow = lDataMap.at(i);
            int j = 0;
            GPage lObj;
            lObj.m_id = lDataRow.at(j++).toInt();
            lObj.m_parentId = lDataRow.at(j++).toInt();
            lObj.m_typeId = lDataRow.at(j++).toInt();
            lObj.m_isDefault = lDataRow.at(j++).toBool();
            lObj.m_name = lDataRow.at(j++);
            lObj.m_path = lDataRow.at(j++);
            lObj.m_idPath = lDataRow.at(j++);
            lObj.m_typeName = lDataRow.at(j++);

            _dom.pushNode();
            GCode lData;
            lData.loadXml(lObj.serialize());
            _dom.loadNode(lData.toData());
            loadPageTree(_dom, lObj.m_id);
            _dom.popNode();
        }
    }

    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::searchPage() {
    GMySQL lMySQL;
    GMySQL::GMaps lDataMap = lMySQL.readMap(GFORMAT(""
            " select t1._id "
            " , t1._parent_id "
            " , t1._type_id "
            " , t1._default "
            " , t1._name "
            " , t1._path "
            " , t1._id_path "
            " , t2._name "
            " from _page t1 "
            " inner join _page_type t2 on 1 = 1 "
            " and t2._id = t1._type_id "
            " %s "
            " order by t2._name, t1._name asc "
            "", m_where.c_str()
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GMySQL::GRows lDataRow = lDataMap.at(i);
        int j = 0;
        GPage* lObj = new GPage;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_parentId = lDataRow.at(j++).toInt();
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_isDefault = lDataRow.at(j++).toBool();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_path = lDataRow.at(j++);
        lObj->m_idPath = lDataRow.at(j++);
        lObj->m_typeName = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::existPage() {
    GMySQL lMySQL;
    int lCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _page t1 "
            " where 1 = 1 "
            " and t1._id = %d "
            "", m_id
    )).toInt();
    m_logs.addLogs(lMySQL.getLogs());
    return (lCount > 0);
}
//===============================================
bool GPage::deletePage() {
    GMySQL lMySQL;
    lMySQL.execQuery(GFORMAT(""
            " delete from _page "
            " where 1 = 1 "
            " and _id = %d "
            "", m_id
    ));
    m_logs.addLogs(lMySQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::isParentDirectory() {
    GMySQL lMySQL;
    int lCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _page t1 "
            " where 1 = 1 "
            " and t1._id = %d "
            " and t1._type_id = 2 "
            "", m_parentId
    )).toInt();
    return (lCount);
}
//===============================================
bool GPage::isTypeNoChange() {
    GMySQL lMySQL;
    int lCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _page t1 "
            " where 1 = 1 "
            " and t1._id = %d "
            " and t1._type_id = %d "
            "", m_id
            , m_typeId
    )).toInt();
    return (lCount);
}
//===============================================
