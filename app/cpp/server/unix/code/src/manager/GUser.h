//===============================================
#ifndef _GUser_
#define _GUser_
//===============================================
#include "GManager.h"
//===============================================
class GUser : public GManager {
public:
    GUser();
    ~GUser();

    bool isValidEmail() const;

    int countUser();
    void loadUser();
    void insertUser();
    void updateUser(const GString& _sql);

    GString serialize(const GString& _code = "user") const;
    void deserialize(const GString& _data, const GString& _code = "user");
    void run(const GString& _data);
    void onLoginUser(const GString& _data);
    void onInsertUser(const GString& _data);
    void onUpdateUser(const GString& _data);

protected:
    int m_id;
    GString m_pseudo;
    GString m_password;
    GString m_email;
    GDateTime m_createDate;
    GDateTime m_updateDate;
};
//===============================================
#endif
//===============================================
