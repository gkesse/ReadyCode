//================================================
#include "GDBusAdaptor.h"
//================================================
GDBusAdaptor::GDBusAdaptor(QObject *parent) : 
QDBusAbstractAdaptor(parent) {
    setAutoRelaySignals(true);
}
//================================================
GDBusAdaptor::~GDBusAdaptor() {

}
//================================================
