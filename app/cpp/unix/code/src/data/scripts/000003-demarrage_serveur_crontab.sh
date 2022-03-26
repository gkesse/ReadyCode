#================================================
# demarrage_serveur_crontab
#================================================
echo "debut du demarrage du serveur.............: OK"
#
GPROJECT_DATA=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data
GPROJECT_SERVER=${GPROJECT_DATA}/server
#
export GPROJECT_DATA
#
cd ${GPROJECT_SERVER}
./server test socket/server/start
#
echo "fin du demarrage du serveur...............: OK"
