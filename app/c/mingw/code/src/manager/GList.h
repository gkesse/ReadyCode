//===============================================
#ifndef _GList_
#define _GList_
//===============================================
#include "GObject.h"
//===============================================
#define GDECLARE_LIST(GDATA) \
        typedef struct _GListNodeO_##GDATA GListNodeO_##GDATA; \
        typedef struct _GListO_##GDATA GListO_##GDATA; \
        \
        struct _GListNodeO_##GDATA { \
            GDATA m_data; \
            GListNodeO_##GDATA* m_next; \
        }; \
        \
        struct _GListO_##GDATA { \
            void* parent; \
            \
            void (*delete)(GListO_##GDATA** obj); \
            void (*clear)(GListO_##GDATA* obj); \
            void (*remove)(GListO_##GDATA* obj, int index); \
            void (*addData)(GListO_##GDATA* obj, GDATA data); \
            void (*setData)(GListO_##GDATA* obj, int index, GDATA data); \
            GDATA (*getData)(GListO_##GDATA* obj, int index); \
            int (*size)(GListO_##GDATA* obj); \
            \
            GListNodeO_##GDATA* m_head; \
        }; \
        \
        GListO_##GDATA* GList_new_##GDATA(); \
        static void GList_delete_##GDATA(GListO_##GDATA** obj); \
        static void GList_clear_##GDATA(GListO_##GDATA* obj); \
        static void GList_remove_##GDATA(GListO_##GDATA* obj, int index); \
        static void GList_addData_##GDATA(GListO_##GDATA* obj, GDATA data); \
        static void GList_setData_##GDATA(GListO_##GDATA* obj, int index, GDATA data); \
        static GDATA GList_getData_##GDATA(GListO_##GDATA* obj, int index); \
        static int GList_size_##GDATA(GListO_##GDATA* obj);
//===============================================
#define GDEFINE_LIST(GDATA) \
        \
        GListO_##GDATA* GList_new_##GDATA() { \
            GObjectO* lParent = GObject_new(); \
            GListO_##GDATA* lChild = (GListO_##GDATA*)malloc(sizeof(GListO_##GDATA)); \
            \
            lChild->parent = lParent; \
            lChild->delete = GList_delete_##GDATA; \
            lChild->clear = GList_clear_##GDATA; \
            lChild->remove = GList_remove_##GDATA; \
            lChild->addData = GList_addData_##GDATA; \
            lChild->setData = GList_setData_##GDATA; \
            lChild->getData = GList_getData_##GDATA; \
            lChild->size = GList_size_##GDATA; \
            \
            lChild->m_head = 0; \
            \
            lParent->child = lChild; \
            return lChild; \
        } \
        \
        static void GList_delete_##GDATA(GListO_##GDATA** obj) { \
            GListO_##GDATA* lObj = *obj; \
            lObj->clear(lObj); \
            GObject_delete(lObj->parent); \
            *obj = 0; \
        } \
        \
        static void GList_clear_##GDATA(GListO_##GDATA* obj) { \
            GListNodeO_##GDATA* lNext = obj->m_head; \
            while(lNext != 0) { \
                GListNodeO_##GDATA* lPrevious = lNext; \
                lNext = lNext->m_next; \
                free(lPrevious); \
            } \
            obj->m_head = 0; \
        } \
        \
        static void GList_remove_##GDATA(GListO_##GDATA* obj, int index) { \
            GListNodeO_##GDATA* lNext = obj->m_head; \
            GListNodeO_##GDATA* lPrevious = 0; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                if(lIndex == index) { \
                    if(lPrevious == 0) obj->m_head = lNext->m_next; \
                    else lPrevious->m_next = lNext->m_next; \
                    free(lNext); \
                    return; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
        } \
        \
        static void GList_addData_##GDATA(GListO_##GDATA* obj, GDATA data) { \
            GListNodeO_##GDATA* lNext = obj->m_head; \
            GListNodeO_##GDATA* lPrevious = 0; \
            \
            while(lNext != 0) { \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
            \
            GListNodeO_##GDATA* lNode = (GListNodeO_##GDATA*)malloc(sizeof(GListNodeO_##GDATA)); \
            lNode->m_data = data; \
            lNode->m_next = 0; \
            \
            if(lPrevious == 0) obj->m_head = lNode; \
            else lPrevious->m_next = lNode; \
        }\
        \
        static void GList_setData_##GDATA(GListO_##GDATA* obj, int index, GDATA data) { \
            GListNodeO_##GDATA* lNext = obj->m_head; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                if(lIndex == index) { \
                    GDATA lData = lNext->m_data; \
                    lNext->m_data = data; \
                    return; \
                } \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
            \
            \
        }\
        \
        static GDATA GList_getData_##GDATA(GListO_##GDATA* obj, int index) { \
            GListNodeO_##GDATA* lNext = obj->m_head; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                GDATA lData = lNext->m_data; \
                if(lIndex == index) return lData; \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
            return 0; \
        } \
        \
        static int GList_size_##GDATA(GListO_##GDATA* obj) { \
            GListNodeO_##GDATA* lNext = obj->m_head; \
            int lSize = 0; \
            \
            while(lNext != 0) { \
                lSize++; \
                lNext = lNext->m_next; \
            } \
            return lSize; \
        }
//===============================================
#define GList_new(GDATA) \
        GList_new_##GDATA
//===============================================
#define GListO(GDATA) \
        GListO_##GDATA
//===============================================
#define GListNodeO(GDATA) \
        GListNodeO_##GDATA
//===============================================
typedef int GINT;
typedef char* GCHAR_PTR;
typedef void* GVOID_PTR;
//===============================================
#endif
//===============================================
