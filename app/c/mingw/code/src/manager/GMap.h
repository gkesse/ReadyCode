//===============================================
#ifndef _GMap_
#define _GMap_
//===============================================
#include "GObject.h"
//===============================================
#define GDECLARE_MAP(GKEY, GVALUE) \
        typedef struct _GMapNodeO_##GKEY##_##GVALUE GMapNodeO_##GKEY##_##GVALUE; \
        typedef struct _GMapO_##GKEY##_##GVALUE GMapO_##GKEY##_##GVALUE; \
        typedef int (*GMAP_EQUAL_##GKEY##_##GVALUE)(GKEY key1, GKEY key2); \
        \
        struct _GMapNodeO_##GKEY##_##GVALUE { \
            GKEY m_key; \
            GVALUE m_value; \
            GMapNodeO_##GKEY##_##GVALUE* m_next; \
        }; \
        \
        struct _GMapO_##GKEY##_##GVALUE { \
            GObjectO* parent; \
            \
            void (*delete)(GMapO_##GKEY##_##GVALUE** obj); \
            void (*setData)(GMapO_##GKEY##_##GVALUE* obj, GKEY key, GVALUE value, void* equal); \
            GVALUE (*getData)(GMapO_##GKEY##_##GVALUE* obj, GKEY key, void* equal); \
            GKEY (*getKey)(GMapO_##GKEY##_##GVALUE* obj, int index); \
            void (*clear)(GMapO_##GKEY##_##GVALUE* obj); \
            void (*remove)(GMapO_##GKEY##_##GVALUE* obj, GKEY key); \
            int (*size)(GMapO_##GKEY##_##GVALUE* obj); \
            int (*equalChar)(void* key1, void* key2); \
            \
            GMapNodeO_##GKEY##_##GVALUE* m_head; \
        }; \
        \
        GMapO_##GKEY##_##GVALUE* GMap_new_##GKEY##_##GVALUE(); \
        static void GMap_delete_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE** obj); \
        static void GMap_clear_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj); \
        static void GMap_remove_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, GKEY key); \
        static void GMap_setData_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, GKEY key, GVALUE value, void* equal); \
        static GVALUE GMap_getData_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, GKEY key, void* equal); \
        static GKEY GMap_getKey_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, int index); \
        static int GMap_size_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj); \
        static int GMap_equalChar_##GKEY##_##GVALUE(void* key1, void* key2);
//===============================================
#define GDEFINE_MAP(GKEY, GVALUE) \
        \
        GMapO_##GKEY##_##GVALUE* GMap_new_##GKEY##_##GVALUE() { \
            GObjectO* lParent = GObject_new(); \
            GMapO_##GKEY##_##GVALUE* lChild = (GMapO_##GKEY##_##GVALUE*)malloc(sizeof(GMapO_##GKEY##_##GVALUE)); \
            \
            lChild->parent = lParent; \
            lChild->delete = GMap_delete_##GKEY##_##GVALUE; \
            lChild->clear = GMap_clear_##GKEY##_##GVALUE; \
            lChild->remove = GMap_remove_##GKEY##_##GVALUE; \
            lChild->setData = GMap_setData_##GKEY##_##GVALUE; \
            lChild->getData = GMap_getData_##GKEY##_##GVALUE; \
            lChild->getKey = GMap_getKey_##GKEY##_##GVALUE; \
            lChild->size = GMap_size_##GKEY##_##GVALUE; \
            lChild->equalChar = GMap_equalChar_##GKEY##_##GVALUE; \
            \
            lChild->m_head = 0; \
            \
            lParent->child = lChild; \
            return lChild; \
        } \
        \
        static void GMap_delete_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE** obj) { \
            GMapO_##GKEY##_##GVALUE* lObj = *obj; \
            lObj->clear(lObj); \
            lObj->parent->delete(&lObj->parent); \
            *obj = 0; \
        } \
        \
        static void GMap_clear_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj) { \
            GMapNodeO_##GKEY##_##GVALUE* lNext = obj->m_head; \
            while(lNext != 0) { \
                GMapNodeO_##GKEY##_##GVALUE* lPrevious = lNext; \
                lNext = lNext->m_next; \
                free(lPrevious); \
            } \
            obj->m_head = 0; \
        } \
        \
        static void GMap_remove_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, GKEY key) { \
            GMapNodeO_##GKEY##_##GVALUE* lNext = obj->m_head; \
            GMapNodeO_##GKEY##_##GVALUE* lPrevious = 0; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                int lEqual = (lKey == key); \
                if(lEqual == 1) { \
                    if(lPrevious == 0) obj->m_head = lNext->m_next; \
                    else lPrevious->m_next = lNext->m_next; \
                    free(lNext); \
                    return; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
        } \
        \
        static void GMap_setData_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, GKEY key, GVALUE value, void* equal) { \
            GMapNodeO_##GKEY##_##GVALUE* lNext = obj->m_head; \
            GMapNodeO_##GKEY##_##GVALUE* lPrevious = 0; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                int lEqual = 0; \
                GMAP_EQUAL_##GKEY##_##GVALUE onEqualCB = equal; \
                if(equal == 0) lEqual = (lKey == key); \
                else lEqual = onEqualCB(lKey, key); \
                if(lEqual == 1) { \
                    lNext->m_value = value; \
                    return; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
            \
            GMapNodeO_##GKEY##_##GVALUE* lNode = (GMapNodeO_##GKEY##_##GVALUE*)malloc(sizeof(GMapNodeO_##GKEY##_##GVALUE)); \
            lNode->m_key = key; \
            lNode->m_value = value; \
            lNode->m_next = 0; \
            \
            if(lPrevious == 0) obj->m_head = lNode; \
            else lPrevious->m_next = lNode; \
        }\
        \
        static GVALUE GMap_getData_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, GKEY key, void* equal) { \
            GMapNodeO_##GKEY##_##GVALUE* lNext = obj->m_head; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                GVALUE lValue = lNext->m_value; \
                int lEqual = 0; \
                GMAP_EQUAL_##GKEY##_##GVALUE onEqualCB = equal; \
                if(equal == 0) lEqual = (lKey == key); \
                else lEqual = onEqualCB(lKey, key); \
                if(lEqual == 1) return lValue; \
                lNext = lNext->m_next; \
            } \
            return 0; \
        } \
        \
        static GKEY GMap_getKey_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj, int index) { \
            GMapNodeO_##GKEY##_##GVALUE* lNext = obj->m_head; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                GVALUE lValue = lNext->m_value; \
                int lEqual = (lIndex == index); \
                if(lEqual == 1) return lKey; \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
            return 0; \
        } \
        \
        static int GMap_size_##GKEY##_##GVALUE(GMapO_##GKEY##_##GVALUE* obj) { \
            GMapNodeO_##GKEY##_##GVALUE* lNext = obj->m_head; \
            int lSize = 0; \
            \
            while(lNext != 0) { \
                lSize++; \
                lNext = lNext->m_next; \
            } \
            return lSize; \
        } \
        \
        static int GMap_equalChar_##GKEY##_##GVALUE(void* key1, void* key2) { \
            if(!strcmp((char*)key1, (char*)key2)) return 1; \
            return 0; \
        }
//===============================================
#define GMap_new(GKEY, GVALUE) \
        GMap_new_##GKEY##_##GVALUE
//===============================================
#define GMapO(GKEY, GVALUE) \
        GMapO_##GKEY##_##GVALUE
//===============================================
#define GMapNodeO(GKEY, GVALUE) \
        GMapNodeO_##GKEY##_##GVALUE
//===============================================
typedef void* GVOID_PTR;
//===============================================
#endif
//===============================================
