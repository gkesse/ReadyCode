//===============================================
#include "GDatabase.h"
//===============================================
static GDatabaseO* m_GDatabaseO = 0;
//===============================================
static GDatabaseO* GDatabase_New();
static void GDatabase_Delete();
static void GDatabase_Open();
static void GDatabase_Load();
static void GDatabase_Update();
static void GDatabase_Save();
//===============================================
static GDatabaseO* GDatabase_New() {
    GDatabaseO* lObj = (GDatabaseO*)malloc(sizeof(GDatabaseO));
        
    lObj->Delete = GDatabase_Delete;
    lObj->Open = GDatabase_Open;
    lObj->Load = GDatabase_Load;
    lObj->Update = GDatabase_Update;
    lObj->Save = GDatabase_Save;
    return lObj;
}
//===============================================
static void GDatabase_Delete() {
    free(m_GDatabaseO);
    m_GDatabaseO = 0;
}
//===============================================
GDatabaseO* GDatabase() {
    if(m_GDatabaseO == 0) {
        m_GDatabaseO = GDatabase_New();
    }
    return m_GDatabaseO;
}
//===============================================
static void GDatabase_Open() {
    printf("on ouvre la base de donnee\n");
}
//===============================================
static void GDatabase_Load() {
    printf("on charge la base de donnees\n");
}
//===============================================
static void GDatabase_Update() {
    printf("on met a jour la base de donnees\n");
}
//===============================================
static void GDatabase_Save() {
    printf("on sauvegarde la base de donnee\n");
}
//===============================================
