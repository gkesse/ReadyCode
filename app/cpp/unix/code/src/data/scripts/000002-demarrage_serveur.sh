#================================================
# demarrage_serveur
#================================================
echo "debut demarrage du serveur................: OK"
#
cd ${GPROJECT_SERVER}
./server test socket/server/start
#
echo "fin demarrage du serveur..................: OK"
