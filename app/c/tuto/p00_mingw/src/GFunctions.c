//===============================================
#include "GFunctions.h"
//===============================================
void smdelete(GVector* _map) {
    for(int i = 0; i < _map->size(_map); i++) {
        GString* lData = _map->get(_map, i);
        lData->delete(&lData);
    }
}
//===============================================
