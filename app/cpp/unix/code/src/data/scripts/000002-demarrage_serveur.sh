#================================================
# demarrage_serveur
#================================================
echo "debut demarrage du serveur................: OK"
#
export "GPROJECT_DATA=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data"
export "GPROJECT_TMP=${GPROJECT_DATA}/tmp"
export "GPROJECT_SCRIPTS=${GPROJECT_DATA}/scripts"
export "GPROJECT_SERVER=${GPROJECT_DATA}/server"
#
cd ${GPROJECT_SERVER}
./server test socket/server/start
#
echo "fin demarrage du serveur..................: OK"
